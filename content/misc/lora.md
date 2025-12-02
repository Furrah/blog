---
title: "Playing with LoRa"
date: 2025-11-28T18:19:48+01:00
tags: []
draft: false
---

I've always been interested in LoRa communications and had read the fabled stories of communicating more than 10km but without trying, how would I know if it is really possible.

# The Plan 

I had downloaded some sample code off the internet but I wasn't really sure what was going on and testing required me to carry my laptop with me which wasn't ideal, especially as it is very cold right now!  

I rewrote the software so that the slave device would send two numbers to the master. The master would then add these numbers together and transmit the summed value back to the slave. If the sum equalled the expected sum then the onboard LED on the slave would flash. As this is all happening the master would be recording each messages received signal strength indicator (RSSI) and signal to noise (SNR) value to a file. 


This meant i could cycle around on my bike and know if i was receiving data or not. HOORAY!

<p align="center"> 
<img src="/misc/images/lora/me_on_bike.jpg" alt="drawing" width="300" loading="lazy"/>
</p>

# Radio Parameters 

### Spreading factor

Larger spreading factors mean larger processing gain, and so a signal modulated with a larger spreading factor can be received with less errors compared to a signal with a lower spreading factor, and therefore travel a longer distance. For example, a signal modulated with the SF12 can travel a longer distance than a signal modulated with the SF7. <a href="https://www.thethingsnetwork.org/docs/lorawan/spreading-factors/" target="_blank"> [1] </a>

The SNR limits are determined by the spreading factor.  

SF7 -7.5dB SF8 -10dB SF9 -12.5dB SF10 -15dB SF11 -17.5dB SF12 -20dB 
<a href= "https://stuartsprojects.github.io/WhatisLoRa.html"  target="_blank" > [2]</a> <a href= "https://se1.isc.heia-fr.ch/lecture/com/lora/" target="_blank"> [3]</a>

If I maximise the spreading factor I sacrifice bit rate but I gain distance. 

### Bandwidth

The bandwidth of a LoRa system determines the chirp rate of each symbol. Lower bandwidth results in a slower chirp, which increases the symbol duration. Longer symbols provide more samples per symbol at the receiver, increasing the processing gain and improving sensitivity. 

To future proof the system I'm going to use 125kHz as this is what is used by LoRaWAN. This is a network protocol that sits on top of the LoRa protocol and grants access to networks of LoRa devices. 

### Coding rate
The coding rate allows for error correction. Increasing the coding rate results in longer data packets but offers increased error correction. For example a coding rate of 4/8 uses 4 bits for data and 4 bits for error correction.

### Preamble
This is the number of symbols used to synchronise with the receiver. LoRaWAN networks require 8 to be used. 

### Power
The EU rules state that the maximum effective isotropic radiated power from a LoRa device is limited to 16dbm. The antenna that came with the board has a gain of 2.81dB. To account for loses I've selected 14dBm.


<table border="1" cellpadding="8" cellspacing="0">
  <thead>
    <tr>
      <th>Parameter</th>
      <th>Value</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Frequency</td>
      <td>868.1 MHz</td>
    </tr>
    <tr>
      <td>Spreading Factor</td>
      <td>12</td>
    </tr>
    <tr>
      <td>Bandwidth</td>
      <td>125 kHz</td>
    </tr>
    <tr>
      <td>Coding Rate</td>
      <td>4/8</td>
    </tr>
    <tr>
      <td>Preamble</td>
      <td>8</td>
    </tr>
    <tr>
      <td>Power</td>
      <td>14 dBm</td>
    </tr>
  </tbody>
</table>


# Results 

The master is somewhere in the village in the north west of the map and the red line shows my bike ride.
The maximum distance I managed to transmit was 4km. Not the 10km I was hoping for. In the background of the picture you can see the village I live in. 

## The Bike Ride


<p align="center"> 
<img src="/misc/images/lora/map.jpg" alt="drawing" width="1000" loading="lazy"/>
</p>

<p align="center"> 
<img src="/misc/images/lora/view.jpg" alt="drawing" width="1000" loading="lazy"/>
</p>

## Why the range might have been limited?

The plot below shows the elevation profile of the yellow max distance line. As you can see its one big valley so free space comms should have been strong. The communication was lost when i went on the other side of the valley near index 80. You can see how i did a little loop on the bike around that area but did not find the signal I was so hoping to find. 


<p align="center"> 
<img src="/misc/images/lora/elevation.jpeg" alt="drawing" width="1000" loading="lazy"/>
</p>

## Signal Strength 

These results are quite spurious. Unfortunately there's little correlation with my actual route and the data points as i recorded no spacial information. All I can tell is that RSSI dropped off alost immeadiately after leaving the house.  

<p align="center"> 
<img src="/misc/images/lora/rssi_snr.png" alt="drawing" width="1000" loading="lazy"/>
</p>


## Files
The files that i used can be download from this link -> <a href="/docs/lora/lora_master_slave.zip" download="lora_master_slave.zip" class="download-link">
  lora_master_slave.zip
  <i data-feather="download" style="margin-left:6px;"></i>
</a>

# Future plan

I want to build a private network where LoRa packets can be transmitted over very long distances. Under normal circumstances, LoRaWAN is used for this: end nodes send their packets to a gateway, and LoRaWAN handles all the difficult parts of managing many devices—such as collision avoidance, retransmissions, acknowledgements, timing, and secure delivery. LoRaWAN removes a huge amount of complexity that would otherwise need to be implemented manually.

However, LoRaWAN assumes that gateways do not talk directly to each other. Instead, gateways forward all received packets to a central network server, which performs the routing, deduplication, and data handling. But in a situation where a central server is not available—or where gateways must relay packets over large distances—this becomes a challenge. The traditional LoRaWAN architecture does not include gateway-to-gateway forwarding.

If we imagine a system with hundreds or even thousands of end nodes, we need a more flexible design where gateways can pass messages between themselves until the data reaches a final collection point. This would allow large coverage areas without relying on continuous access to a central server.

Below is how I think such a system could be implemented.


<div class="custom-image-switch">
<img src="/misc/images/lora/High_level_outline-light_.png" class="light-mode no-style-image" alt="Light Mode Image">
<img src="/misc/images/lora/High_level_outline-dark.png" class="dark-mode no-style-image" alt="Dark Mode Image">
</div>