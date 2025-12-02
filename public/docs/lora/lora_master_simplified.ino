#include <RadioLib.h> //Version 6.4.2

#define LED_PIN PB5  // LED to flash during transmit

STM32WLx radio = new STM32WLx_Module(); // create radio object

// define pins used for radio transmission / receive
static const uint32_t rfswitch_pins[] = { PA4, PA5, RADIOLIB_NC };
static const Module::RfSwitchMode_t rfswitch_table[] = {
  {STM32WLx::MODE_IDLE,  {LOW, LOW}},
  {STM32WLx::MODE_RX,    {HIGH, LOW}},
  {STM32WLx::MODE_TX_HP, {HIGH, HIGH}},
  END_OF_MODE_TABLE
};

// callback flags
volatile bool receivedFlag = false;
volatile bool transmittedFlag = false;

// buffers
uint8_t rxBuf[3]; // seq + a + b
uint8_t txBuf[2]; // seq + sum

// state machine states
typedef enum { 
    STATE_WAIT_RX, 
    STATE_WAIT_TX 
    } State_t;

State_t state = STATE_WAIT_RX;

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
    Serial.begin(115200);
    while(!Serial);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    radio.setRfSwitchTable(rfswitch_pins, rfswitch_table);

    // SF: 12 - high spread factor for maximum transmission time resulting in maximum range
    int st = radio.begin(868.1, 125.0, 12, 8, 0x12, 14, 12, 1.7, 0); 

    // radio has failed to initialise
    if(st != RADIOLIB_ERR_NONE) { 
        Serial.print("Radio init failed! "); 
        Serial.println(st); // print error code 
        while(true); 
    }

    // callback function when received or transmitted a packet
    radio.setDio1Action(setFlag);

    // start listening immediately
    radio.startReceive();
    
    Serial.println("Master ready");
}

void loop() {
  switch(state) {
    case STATE_WAIT_RX: {
      digitalWrite(LED_PIN, LOW); // LED OFF while waiting for RX

      if(receivedFlag) {
        receivedFlag = false;
        int st = radio.readData(rxBuf, 2);
        float rssi = radio.getRSSI();
        float snr  = radio.getSNR();
        
        if(st != RADIOLIB_ERR_NONE) {
          Serial.printf("RX error: %d\n", st);
          radio.startReceive(); // try again
          break;
        }

        // print signal data
        Serial.print("RSSI: ");
        Serial.println(rssi);

        Serial.print("SNR: ");
        Serial.println(snr);

        uint8_t a = rxBuf[0];
        uint8_t b = rxBuf[1];
        uint8_t sum = a + b;
        Serial.printf("Received %d + %d = %d\n", a, b, sum);

        txBuf[0] = sum;

        transmittedFlag = false;
        radio.startTransmit(txBuf, 1);
        state = STATE_WAIT_TX;
      }
      break;
    }

    case STATE_WAIT_TX: {
      flash_led();

      if(transmittedFlag) {
        transmittedFlag = false;
        Serial.println("TX complete, back to RX");
        radio.startReceive(); // restart RX after TX
        state = STATE_WAIT_RX;
      } 
      break;
    }
  }
}
