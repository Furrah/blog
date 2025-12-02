#include <RadioLib.h> //version 6.4.2     

#define LED_PIN PB5   // LED flash when Rx data is as expected 

STM32WLx radio = new STM32WLx_Module();

static const uint32_t rfswitch_pins[] = { PA4, PA5, RADIOLIB_NC };
static const Module::RfSwitchMode_t rfswitch_table[] = {
  {STM32WLx::MODE_IDLE,  {LOW,  LOW}},
  {STM32WLx::MODE_RX,    {HIGH, LOW}},
  {STM32WLx::MODE_TX_HP, {HIGH,  HIGH}},
  END_OF_MODE_TABLE
};

// flags
volatile bool receivedFlag = false;
volatile bool transmittedFlag = false;

// buffers
uint8_t txBuf[2];   // we send 2 random numbers
uint8_t rxBuf[1];   // we expect 1-byte sum

uint8_t a, b; // store random numbers 
uint8_t expectedSum; 

// state machine enums
typedef enum {
    STATE_IDLE,
    STATE_WAIT_TX,
    STATE_WAIT_RX,
    STATE_WAIT_DELAY
} State_t;

State_t state = STATE_IDLE;

unsigned long lastAction = 0; // used for timout of RX
const unsigned long SEND_DELAY = 5000; // if transmission is good send another transmission in 5 seconds
const unsigned long RX_TIMEOUT = 10000;  // RX has failed resend if no reply after 10s


void flash_led(){
    digitalWrite(LED_PIN, LOW);   
    delay(200);               
    digitalWrite(LED_PIN, HIGH);    
}

// ---------------- CALLBACK ----------------
void setFlag(void) 
{
  uint16_t irqstatus = radio.getIrqStatus();
  if(irqstatus == RADIOLIB_SX126X_IRQ_RX_DONE) {
    receivedFlag = true;
  }
  else if(irqstatus == RADIOLIB_SX126X_IRQ_TX_DONE) {
    transmittedFlag = true;
  }
  else {
    receivedFlag = false;
    transmittedFlag = false;
  }
}


void setup() {

  //LED PIN SETUP: stops the red led flashing on startup 
  pinMode(LED_PIN, OUTPUT_OPEN_DRAIN);
  digitalWrite(LED_PIN, HIGH);  // LED is active low. 
  pinMode(LED_PIN, OUTPUT);     // now enable push-pull output

  // SERIAL SETUP
  Serial.begin(115200);
  while(!Serial);

  // seed random number generator 
  randomSeed(HAL_GetTick()); 

  // Initialise radio   
  radio.setRfSwitchTable(rfswitch_pins, rfswitch_table);
  int st = radio.begin(868.1, 125.0, 12, 8, 0x12, 14, 12, 1.7, 0); // optimised for long range data transmission

  // Radio has failed to initalise
  if(st != RADIOLIB_ERR_NONE) {
    Serial.print("Radio init failed! ");
    Serial.println(st); //print error code
    while(true);
  }

  // callback function when received or transmitted a packet
  radio.setDio1Action(setFlag);  

  Serial.println("Slave ready");
  lastAction = HAL_GetTick();
}


void loop() {

    unsigned long now = HAL_GetTick(); // get current time of loop

    switch(state) {
        case STATE_IDLE:
            a = random(0, 256);
            b = random(0, 256);
            expectedSum = a + b;

            txBuf[0] = a;
            txBuf[1] = b;

            transmittedFlag = false;
            radio.startTransmit(txBuf, 2);

            Serial.printf("\n---- NEW EXCHANGE ----\nGenerated numbers: %d + %d\n", a, b);
            state = STATE_WAIT_TX;
            break;

        case STATE_WAIT_TX:
            if(transmittedFlag) {
                transmittedFlag = false;
              
                Serial.println("TX complete, waiting for sum...");
                radio.startReceive();  // open RX window
                lastAction = now; // store time for Rx timeout
                state = STATE_WAIT_RX;
            }
            break;

        case STATE_WAIT_RX:
            if(receivedFlag) {
                receivedFlag = false;
                int st = radio.readData(rxBuf, 1);

                // rssi and snr functions must be called as close to reading data as possible
                float rssi = radio.getRSSI();
                float snr  = radio.getSNR();                
                
                // Rx failed, go back to idle and try again
                if(st != RADIOLIB_ERR_NONE){
                    Serial.printf("RX failed, code: %d\n", st);
                    state = STATE_WAIT_DELAY;
                }

                // Rx is good. Check data
                else {
                    uint8_t sum = rxBuf[0];

                    Serial.printf("Received sum: %d, expected: %d\n", sum, expectedSum);

                    Serial.print("RSSI: ");
                    Serial.println(rssi);

                    Serial.print("SNR: ");
                    Serial.println(snr);

                    if(sum == expectedSum) {
                        Serial.println("SUM MATCHES (OK)");
                        flash_led(); // hoooray! flash the led. 
                    }
                    else {
                        Serial.println("SUM DOES NOT MATCH (ERROR)");
                    }

                    state = STATE_WAIT_DELAY;     
                }
                    lastAction = now; // store time                
            }
            else if(now - lastAction > RX_TIMEOUT) {
                Serial.println("RX timeout, retrying...");
                state = STATE_IDLE; // will generate new numbers
            }            
            break;

        case STATE_WAIT_DELAY:
            // Do nothing until delay passes
            if(now - lastAction >= SEND_DELAY) {
                state = STATE_IDLE;
            }
            break;
    }
}
