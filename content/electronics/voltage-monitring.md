---
title: "Voltage Monitoring"
date: 2019-11-22T23:54:08Z
tags: ['power', 'supply','monitoring', 'op amps', 'ADC', 'ADA4096', 'LTC2990']
draft: false
---

The ADA4096 operational amplifier comes in a dual and quad package. Its inputs are protected by overvoltage protection diodes making it a perfect candidate for monitoring voltages, especially when power to the IC could be lost.  

<a href=https://www.analog.com/media/en/technical-documentation/data-sheets/ADA4096-2_4096-4.pdf target="_blank">ADA4096 Datasheet</a>



The LTC2990 is a Quad I2C voltage, current, and temperature monitor. When used in conjunction with the ADA4096 it makes a simple monitoring interface through I2C. 

<a href=https://www.analog.com/media/en/technical-documentation/data-sheets/LTC2990.pdf target="_blank">LTC2990 Datasheet</a>

The LTC2990 supply voltages are between 3.3V and 5V so each voltage to be monitored should fall within the range of the chosen supply voltage. The figure below shows a simple circuit to monitor positive and negative voltages. Filtering, although not necessary, adds some stability to the measured voltages. A recommended capacitor is 100nF.


<p align="center"> 
<img src="/electronics/images/voltage-monitoring.svg" alt="drawing" width="600">
</p>

The Datasheet provides many different applications of the LTC2990. Below the suggested voltage monitoring circuit is shown. By adding the ADA4096 we simply buffer the input voltages.

<p align="center"> 
<img src="/electronics/images/LTC2990.png" alt="drawing" width="600">
</p>