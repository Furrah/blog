---
title: "Greenhouse"
date: 2022-04-24T22:02:52+01:00
tags: []
draft: true
---

## Introduction 

Back in 2013 I'd have just completed my 3rd year at university and was pretty interested in grow cells for vertical farming (after my degree I even had a PHD setup on this topic! Alas i decided to venture into the big bad world) and wanted to build an automated greenhouse for myself. I was hyped! I dug a trench from the house to the greenhouse and laid armoured cable. Installed a Raspberry pi and  and used powerline networking to connect to the internet. I got as far as installing a watering system using some solenoid valves that connected to the mains water. Things were looking pretty good. Finally, I had also installed around 50 temperature sensors with an aim of creating a homogenous temperature distribution within the greenhouse with heaters and fans. I never got that far. Well life happened since then and its now 2022 and I'm thinking about that damn greenhouse again. 

## Why Greenhouse?

So, what triggered this thought process? In December of 2021 it was announced that energy prices would be sky rocketing in the U.K. from April 2022 with no real reason other than energy companies wanting more money and the government not giving a damn about the citizens that inhabit the country they apparently govern. Anyway... I found an insane deal for some solar panels on Ebay. £45 for a 500W solar panel. This is crazy cheap. Now, the glass is damaged but still... This is crazy crazy cheap. I bought four. 

I now have 2000W of potential solar power that I can utilise but no real place to put it. I don't own a house and I dream of growing tropical plants. Remotely operated greenhouse at the parents house it is then. 

## What's the plan Stan? What's the aim of the game?

1. Build a solar system.
2. Use power to grow plants. 
3. Sell plants to pay for greenhouse?
4. Sell excess solar? 
5. Visit parents often. 
6. Use dad as technician, update C.V with newly acquired people management skills. 
7. Hydroponics? 
8. HAVE FUN

## Lets Begin! SOLAR SYSTEM 

The basic components of a solar system include the following;

1. Solar panels.
2. Batteries.
3. Charge controller. 

Whilst picking up the solar panels the seller invited me into his house where he had around 30 uninterruptible power supply telecommunication batteries sitting at the base of his stairs. 12V 170Ah lead acid batteries produced in 2020. I bought 2 at £150 each. 

I now have a theoretical energy of 4kWh. This is pretty good considering the average 2 bedroom household in the U.K. uses around 8kWh per day of energy. 
It's a good start and I can obviously add more batteries should it be required. I will soon learn that there is a lot to learn about batteries... 


**Design decision number one.**
1. choose operating voltage. 

I've decided to go for a 24V system to try and keep cable thickness down and mitigate ohmic loses but also because a lot of industrial electronics operates off a 24V bus. The downside is that if I want to extend the energy storage I need to buy batteries in groups of two.

A charge controller is needed to link them together but before I speak about that, let's look at the solar panel specification. 

**Solar Panel Specification**
* Maximum power - 495W±3%
* Maximum power voltage - 43.1V 
* Maximum power current - 11.49A 
* Open Circuit Voltage - 51.3V±3% 
* Short Circuit Current 12.0A±5%


### Charge controller 

There are two types of charger, PWM and MPPT. PWM controllers are around 75-80% efficient and can only be used when the solar voltage is roughly around that of the battery. As our system is 24V and the panels are 43.1V an MPPT charger is required, which is the obvious choice as its efficiencies are in the 98%+ area. 

I settled on an Epever AN4210 MPPT controller for £117. It can output 1kW at full power into a 24V system and also mentions in the manual that multiple modules can be paralleled together. Perfect, I love a modular system. I would later find out that this is not the case after emailing their customer support and asking if it really can be done... Albeit, this was a little too late into the game. 

**Epever AN4210 Specification**























