---
title: "USB Design Guide"
date: 2019-11-30T12:59:24+01:00
tags: ['USB', 'design', 'guide', 'microstrip', 'differential', 'single-ended', 'ESD']
draft: false
---


## Key features

* USB connector 
* ESD protection 
* Differential microstrip design for USB 


## USB Connector 
For this particular design I have chosen a USB-B female connector from Mouser.
<div>
  <table class="w3-table-all w3-card-4">
    <tr>
      <th>Mouser #</th>
      <th>Manufacturer #</th>
      <th>Manufacturer </th>
    </tr>
    <tr>
      <td>571-292304-1</td>
      <td>292304-1 </td>
      <td>TE Connectivity</td>
    </tr>
  </table>
</div>

<br>

<p align="center"> 
<img src="/electronics/images/usb-b.png" alt="drawing" width="100">
</p>

The USB connector datasheet can be found
<a href="https://www.mouser.ch/datasheet/2/418/NG_DS_7-1773442-0_0306-1258760.pdf" target="_blank">here.</a> 
## ESD Protection 

 The 
<a href="https://assets.nexperia.com/documents/data-sheet/PRTR5V0U4Y.pdf" target="_blank">PRTR5V0U4Y</a> 
is designed to protect Input/Output (I/O) ports that are sensitive to capacitive load, such as USB 2.0, Ethernet and DVI from destruction by ElectroStaticDischarge (ESD). It provides protection to downstream signal and supply components from ESD voltages as high as ±8 kV (contact discharge).The PRTR5V0U4Y incorporates four pairs of ultra-low capacitance rail-to-rail diodes plus a Zener diode. The rail-to-rail diodes are connected to the Zener diode which allows ESD protection to be independent of supply voltage. The PRTR5V0U4Y is fabricated using thin film-on-silicon technology integrating four ultra-low capacitance rail-to-rail ESD protection diodes in a miniature 6-lead SOT363 package.

<p align="center"> 
<img src="/electronics/images/USB-routing.PNG" alt="drawing" width="700">
</p>


## Microstrip Design 


<a href=https://www.analog.com/en/analog-dialogue/articles/switching-in-usb-consumer-applications.html target="_blank">USB Design</a>
requires 45 Ohm single ended traces with a differential impedance of 90 Ohm. I like to use the calculators from www.mantaro.com to design microstrip lines. The differential microstrip calculator can be found <a href=https://www.mantaro.com/resources/impedance-calculator.htm
 target="_blank">here.</a>
The table below shows some initial design parameters to start the design.


<table class="w3-table-all w3-card-4">
  <tr>
    <th>Parameter</th>
    <th>Value</th>
  </tr>
  <tr>
    <td>Trace Width (mm)</td>
    <td>0.59</td>
  </tr>
  <tr>
    <td>Trace Seperation (mm)</td>
    <td>1</td>
  </tr>
  <tr>
    <td>Trace Thickness (mm)</td>
    <td>0.035</td>
  </tr>
  <tr>
    <td>Relative Dielectric Constant</td>
    <td>4.5</td>
  </tr>
  <tr>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Differential Line Impedance</td>
    <td>88.678</td>
  </tr>
  <tr>
    <td>Single Ended Line Impedance</td>
    <td>45.228</td>
  </tr>
</table>  
<br>

