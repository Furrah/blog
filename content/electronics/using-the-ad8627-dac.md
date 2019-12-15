---
title: "Using the AD5627 DAC"
date: 2019-12-08T11:23:58+01:00
tags: ['DAC', 'AD5627', 'level shifting']
draft: false
---

## Introduction 

The 
<a href=https://www.analog.com/media/en/technical-documentation/data-sheets/AD5627R_5647R_5667R_5627_5667.pdf target="_blank">AD5627RBRMZ (Datasheet)</a> is part of a series of 12/14/16 bit nano DACs with an I2C interface.
The DAC we are interested in is the 12 bit AD5627RBRMZ which has a 5ppm/˚C internal reference and can operate upto 5V output.

## Design 

A typical I2C bus operates at 3.3 Volts. In order to use the full scale output of the DAC (5V) a level shifter is required as the AD5627 sees an I2C high at 0.8 Vcc - 4V.

For this I am using the 
<a href=https://www.nxp.com/docs/en/data-sheet/PCA9306.pdf target="_blank">PCA9306 Bidirectional I2C level shifter (Datasheet)</a> 

## Circuit 
<p align="center"> 
<img src="/electronics/images/ad5627.PNG" alt="drawing" width="100%"/>
</p>
<br>

## Operation

#### Addressing
The 5 MSBs are 00011. The address pin is tied to GND which makes the address of the chip 0001111 = 0xF

#### Set Internal Reference
On start up the internal reference is set to off. To turn it on send the command 3F,00,01

Command - Internal reference setup (on/off )<br>
Address - Both DACS <br>
Data - nothing <br>
LDAC control - The DAC registers are updated after new data is read in. <br>

Byte 1 - 0x3F - 00111111 <br>
Byte 2 - 0x00 - no data to send<br>
Byte 3 - 0x01 - 0000001 <br>

#### Setting Output Voltage
The voltage is set with a 16 bit data string but as the DAC is 12 bits the last 4 LSBs are not used. 

The voltage is set with a command followed by an address. 
command - Write to and update DAC channel n - 011
address - both DACs - 111

Bit 1 is reserved 
Bit 2 should be set to zero for 3 byte operation of chip

00011111 - 1F 

Data - 12 bits to make full scale value FFF so 50% voltage would be 7FF.

last 4 bits should be set to 1 for operation - F 

3 bytes = 0x1F,0x7F,0xFF









