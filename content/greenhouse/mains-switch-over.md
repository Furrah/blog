---
title: "Mains Switch Over"
date: 2024-09-15T15:56:29+02:00
tags: []
draft: false
---

# Introduction

My dad has a large fish pond and would like to use the solar system to run the pumps, which require 150W of power. Can the solar system run the pumps 24/7?

# Battery Capacity Overview

The battery system has a capacity of 170Ah at 24V, equating to 4kWh of total stored energy. In practice, the battery state of charge (SoC) should not drop below 20% to maintain battery health, resulting in 3.26kWh of usable energy.

This would run the pumps for approximately: <nr>

**3.26kWh/150W = 21.76 hours** 

To edge on the side of caution I will also assume that the real capacity is less than this as the batteries are 4 years old now. A safety factor of 0.85 would result in 18.5 hours of continuous pump use.


My hope is that during the day the batteries will be charged up and the system will be able to run the pumps throughout the night. 

If the state of charge falls below 20%, the system should cut off to protect the batteries, but the pumps must continue to operate. To achieve this, an interface is required to switch the power supply from solar to mains when necessary.


# High Level Outline

For simplicity and ease of maintenance I would like to try and avoid any form of software. This should be achievable with the design below.

<p align="center"> 
<img src="/greenhouse/images/mains_switchover/HLD.png" alt="drawing" width="800"/>
</p>

**Fail Safe**

If the solar system is off, the default state of the interface relay connects the pumps to the house mains and keeps the pumps running. 

**Normal Operation**

When the solar system is on, the Victron battery protect unit measures the battery voltage and enables the 24V system if the system voltage is above a programmable threshold value.

The alarm output of the battery protect unit in this scenario is low which results in the time delay relay staying in its normally connected state. This in turn enables the interface relay connecting the inverter to the pumps. 

Should the system voltage go below the threshold value the time delay relay is triggered for 24 hours and the pumps are connected to mains power. Hopefully this is enough time for the batteries to be recharged by the solar system. 


# Components

**Interface Relay**

The relay must be able to cope with the switching current of the pumps which draw 0.65A (150W/230VAC). The [Phoenix Contact RIF-2-RSC-LDP-24DC/4X21 Series Interface Relay, DIN Rail Mount, 24V dc Coil, 4PDT, 4-Pole](https://uk.rs-online.com/web/p/electromechanical-interface-relays/1750529?gb=s) has a switching current of 1A at 230VAC and a maximum continuous draw of 6A.

<div class="container">
  <div class="row">
    <div class="col">
     <p align="center"> 
		<img src="/greenhouse/images/mains_switchover/change_over_relay.png" alt="drawing" width="300px"/>
	</p>
    </div>
  <div class="col">
     <p align="center"> 
		<img src="/greenhouse/images/mains_switchover/interface_relay_wiring.png" alt="drawing" width="300px"/>
	</p>
  </div>
</div>
</div>


**Time Delay Relay**

<div class="container">
  <div class="row">
    <div class="col">
      The <a href="https://www.geya.net/product/single-function-time-relay-grt8-b1/" target="_blank">GRT8-B1</a> is a 24V time delay relay that can be configured to delay up to 10 days with a reset function.
    </div>
    <div class="col">
      <p align="center">
        <img src="/greenhouse/images/mains_switchover/time_delay_Relay.jpg" alt="Time Delay Relay" width="300"/>
      </p>
    </div>
  </div>
</div>


**Victron Inverter**

<div class="container">
  <div class="row">
    <div class="col">
      The pumps require 150W of power so I have chosen the <a href="https://www.12voltplanet.co.uk/victron-energy-phoenix-pure-sine-wave-inverter-24v-375va-vedirect-enabled.html?srsltid=AfmBOoqnb53QjVgjuPILJef0MEc9qZr6HiRMyV2cSwMxgBe4dQrV1NCN" target="_blank">Victron 24V 375VA Inverter</a> despite there being a 250VA version available to better future proof the design.
    </div>
    <div class="col">
		<p align="center"> 
		<img src="/greenhouse/images/mains_switchover/victron_inverter_375va.jpg" alt="drawing" width="500"/>
		</p>
    </div>
  </div>
</div>


**Battery Protect**

<div class="container">
  <div class="row">
    <div class="col">
     	The Victron Battery Protect automatically disconnects loads when the system voltage drops below a programmable threshold. At 20% state of charge, the 12V170FS battery has a cell voltage of 2.00V that results in a total system voltage of 24V. This corresponds to Program 8 in the datasheet which will disconnect at 24V and reconnect once the system voltage rises to 26V. I’ve included a time delay relay because the MPPT charge controller from the solar system applies a daily boost voltage to the battery, which could falsely indicate that the battery is fully charged.
    </div>
    <div class="col">
		<p align="center"> 
		<img src="/greenhouse/images/mains_switchover/batteryprotect-12-24v-65a.jpg" alt="drawing" width="500"/>
		</p>
    </div>
  </div>
</div>



# BOM 

| Part Number                                   | Description       | Manufacturer    | Supplier     | Cost (£)   |
| --------------------------------------------- | ----------------- | ------------    | -------      |-------     |
| 2903320                                       | Interface Relay   | Phoenix Contact | RS           | 13.26      |
| GRT8-B1                                       | Time Delay Relay  | Geya            | Amazon       | 15.19      |
| Phoenix Pure Sine Wave Inverter - 24V 375VA   | Inverter          | Victron         | 12V Planet   | 107.14     |
| Smart Battery Protect 12/24V - 65A            | Battery Protect   | Victron         | 12V Planet   | 46.18      |
|                                               |                   |                 |              | **181.77** |




# Wiring Diagram

<p align="center"> 
<img src="/greenhouse/images/mains_switchover/SLD.png" alt="drawing" width="900"/>
</p>

