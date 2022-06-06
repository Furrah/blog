---
title: "Greenhouse"
date: 2022-04-24T22:02:52+01:00
tags: []
draft: false
---

## Introduction 

Back in 2013 I'd have just completed my 3rd year at university and was pretty interested in grow cells for vertical farming and wanted to build an automated greenhouse for myself. After my degree I even had a PHD setup on this topic! Alas i decided to venture into the big bad world. Anyway, I was hyped to built my own automated greenhouse! I dug a trench from the house to the greenhouse and laid armoured cable. Installed a Raspberry pi and used powerline networking to connect to the internet. I got as far as installing a watering system using some solenoid valves that connected to the mains water. Things were looking pretty good. Finally, I had also installed around 50 temperature sensors with an aim of creating a homogenous temperature distribution within the greenhouse with heaters and fans. I never got that far but I did collect a lot of useless data... Well life happened since then and its now 2022 and I'm thinking about that damn greenhouse again. 

## But Why?

So, what triggered this thought? In December of 2021 it was announced that energy prices would be sky rocketing in the U.K. from April 2022 with no real reason other than energy companies wanting more money and the government not giving a damn about the citizens that inhabit the country they apparently govern. Anyway... I found an insane deal for some solar panels on Ebay. £45 for a 500W solar panel. This is crazy cheap. Now, the glass is damaged but still... This is crazy crazy cheap. I bought four. 

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

Epever AN4210 Datasheet Specification

* Rated current - 40A
* Battery voltage range 8 - 32V
* Max PV open circuit voltage 100V/92V
* Max PV input power 1040W/24V
* RS485 Interface 
* Efficiency for 24V system - 97.00%

In the manual for the charge controller the maximum PV Array power is 1560W, however, it can only output 1kW. This means in summer the system will be saturated but in the winter it will allow it to get a little extra boost when the dark days come rolling in. 

On page 7 of the manual found [here](https://www.epever.com/upload/cert/file/1811/Tracer-AN-SMS-EL-V1.0.pdf) it says 

```
"Multiple same models of controllers can be installed in parallel on the same battery bank 
to achieve higher charging current. Each controller must have its own solar module(s)"
```

I emailed Epever to make sure this could be done as I was dubious. 

**Me**
```
"Please could you confirm that multiple Tracer AN 4210 modules can be connected in parallel to the same 
battery system. Are there any additional electronics that should be considered when installing?
Thanks,
Joe"
```

**Epever**
```
"Hi Joe Spencer,

Generally, we don't recommend to parallel connect multiple controllers. 
Because of they have detective deviation,maybe affect each other when battery is almost charge full, 
such as one more, one little. It is not good for your battery bank.

Of course, you can do like so if you willing to take the risk for using.

Thanks in advance and have a wonderful day!

Best Regards
Bianca Chen
EPEVER Support"
```
Damn.

## Basic Design 

All the essential ingredients have been selected. They now need to be wired together in the safest way possible. 

The Epever manual begins that process by recommending a circuit breaker between the PV array and the charge controller as well as a fuse between the positive output terminal of the charge controller and the battery.


<p align="center"> 
<img src="/electronics/images/greenhouse/Epever_design.PNG" alt="drawing" width="700"/>
</p>

**Breaker**

DC Circuit Breaker: [DZ47-63Z-2P 6kA 32A 500V](http://donar.messe.de/exhibitor/hannovermesse/2017/U593078/breaker-eng-350150.pdf)

The charge controller is rated to output 1kW of power. The solar panels voltage varies but we can expect the 1kW to be generated at the best power output which is 43.1 V. 1000W/43.1V = 23A. This is the nominal current for operation, so for standard operating conditions a safety factor of ~1.5 is acceptable. Thus a 32A breaker is chosen. 

**Fuse**

The manual says

```
CAUTION: A fuse which current is 1.25 to 2 times the rated current of the
controller, must be installed on the battery side with a distance from the
battery not greater than 150 mm
```

As the rated current is 40A I chose a 50A fuse. 

## Cable and Connectors

**Solar Side Cable**

Commercial PV cable generally comes in two sizes, 4mm and 6mm. [This website](https://solarshop.baywa-re.lu/core/media/media.nl?id=39964&c=6376560&h=1HNFZoC2y87TnRjVvF9_YoWGIwH0RTM2M_9GgebL2ZDTYHSV&_xt=.pdf) gives information on the current carrying capacity of PV cable. As I may want to add more panels in the future I chose 6mm cable which is safe upto 70A in free air at 60 C.

**Battery Side Cable**

The Epever controller accept a maximum cable size of 16mm. At the time of building I only had excess 25mm^2 cable left so i had to do a little bit of a trim down. Ebay sellers offer to add the lug connectors to the cable for you which is useful as I don't own a hydraulic crimper...

**Connectors**

The 3 panels are connected in parallel using connector like the ones shown below. These are rated to 30A which is safe but i'd like to upgrade these at some point to [this connector](https://www.amazon.co.uk/dp/B088N8WF2P/ref=sspa_dk_detail_2?pd_rd_i=B088N8C4ZM&pd_rd_w=YzkMc&content-id=amzn1.sym.9ca56d9d-fbab-435c-8df2-efa89f421d75&pf_rd_p=9ca56d9d-fbab-435c-8df2-efa89f421d75&pf_rd_r=HHN62CWDVQRTJRQEWKRX&pd_rd_wg=MZAbn&pd_rd_r=b09ae58d-5d7d-4280-bd42-c5841733051b&s=industrial&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFZVjE2NDRZWjAwQTcmZW5jcnlwdGVkSWQ9QTAyMTgyMjAxNUhVOU9WUE9JR1M2JmVuY3J5cHRlZEFkSWQ9QTEwMTg2MzUxN000RDZLWEpUUzI1JndpZGdldE5hbWU9c3BfZGV0YWlsJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ&th=1) which are rated to 50A and are IP68 dust and water rated. It's not necessary for now but hopefully if the system grows...

<p align="center"> 
<img src="/electronics/images/greenhouse/Solar_Connector.PNG" alt="drawing" width="300"/>
</p>


## Let The Build Begin


<p align="center"> 
<img src="/electronics/images/greenhouse/IMG_5667.jpeg" alt="drawing" width="700"/>
</p>

<p align="center"> 
<img src="/electronics/images/greenhouse/IMG_5668.jpeg" alt="drawing" width="700"/>
</p>

<p align="center"> 
<img src="/electronics/images/greenhouse/IMG_6082.jpeg" alt="drawing" width="700"/>
</p>



<p align="center"> 
<img src="/electronics/images/greenhouse/IMG_6115.jpeg" alt="drawing" width="700"/>
</p>

<p align="center"> 
<img src="/electronics/images/greenhouse/IMG_6125.jpeg" alt="drawing" width="700"/>
</p>

<p align="center"> 
<img src="/electronics/images/greenhouse/IMG_6130.jpeg" alt="drawing" width="700"/>
</p>

<p align="center"> 
<img src="/electronics/images/greenhouse/IMG_6475.jpeg" alt="drawing" width="700"/>
</p>















