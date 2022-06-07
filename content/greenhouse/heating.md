---
title: "Heating"
date: 2022-06-07T15:49:20+01:00
tags: []
draft: false
---

## Can I heat the greenhouse?

My first idea was to see if it is possible to maintain a 5 degree C temperature gradient between the inside and outside of the greenhouse. I wondered how much power I would need to do this. Below is a calculation to do just that but getting the constants right is pretty tricky and ambiguous at best.

The calculation is based upon [this tutorial](https://www.engineersedge.com/heat_transfer/singlepane_window_heat_loss_13863.htm) and these websites give a good idea of what the constants for the windows might be. 

[Engineering edge - list of heat transfer coefficients](https://www.engineersedge.com/heat_transfer/convective_heat_transfer_coefficients__13378.htm)<br>
[Engineering edge - double glazed window heat transfer coefficients](https://www.engineersedge.com/heat_transfer/heat_transfer_coefficients_13822.htm)<br>
[Bre Group -  is bigger always better - triple better than double?]( https://www.bregroup.com/insights/is-bigger-always-better-triple-better-than-double/)
```python
k_glass = 1.1 # https://www.bregroup.com/insights/is-bigger-always-better-triple-better-than-double/
h_inside = 5 # can vary from 5-37 for free air convection . examples seen have used 8 - 10 
h_outside = 15 # can vary from 10 to 100 depending of wind speed outside. examples seen have used 15-40

L = 28e-3 # thickness of window 
A = 15 #m2 area of window

R_cond = L / (k_glass * A)
R_conv_i = 1 / (h_inside * A)
R_conv_o = 1 / (h_outside * A)

R_total =  R_cond + R_conv_i + R_conv_o

T_inside = 5
T_outside = 0 

Q_dot = (T_inside - T_outside) / R_total

print(f'{Q_dot:.2f}W')
```

This gives 256.74W but if you play about with the numbers you'll quickly see this can vary quite a lot, particularly for the inside heat transfer coefficient.

<form id="form" onsubmit="return false;">
	k glass:   <input  type="text" id="k_glass" value="1.1" />
    H Inside:  <input  type="text" id="h_inside" value="5" />
    H Outside: <input  type="text" id="h_outside" value="15" />
    <input  type="submit" onclick="calculate_power_loss();" /><br><br>
    <center><h3>Power loss: <span id="myText"></span></h3></center>
</form>


What does this mean? Well, I can assume that something between 300W and 600W is required to maintain a positive temperature differential. After some googling I found [these](https://www.amazon.co.uk/gp/product/B07BK1VQTP/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1). At the time the site said they were 300W and operated on 24V with a built in fan. If you click on the link now it says 250W... They cost £25 on amazon and I bought two to be delivered the next day to my parents house. DO NOT BUY FROM AMAZON. You can find these on aliexpress in the £7 range. 

I have never measured the power consumption of these devices but I can assume they are in the 250-300W area.
Here they are mounted on the wall.  

<!-- <p align="center"> 
<img src="/greenhouse/images/greenhouse/heater.png" alt="drawing" width="300"/>
</p> -->

<p align="center"> 
<img src="/greenhouse/images/greenhouse/IMG_0161.jpeg" alt="drawing" width="500"/>
</p>


## How are they operated?

To control the heaters a switching device is required. After looking for a cheap commercial option on the internet I came to the conclusion that a custom board was required for switching loads above 10A at 24V. Behold the four channel relay PCB. It features optically isolated inputs and 16A relays that operate off a 24V coil with an LED indicator. Version 2 did include current monitoring but the project became corrupted and so I ended up with version 1. Here is the [datasheet](https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=RT1_bistable&DocType=DS&DocLang=English) for the relay.

<p align="center"> 
<img src="/greenhouse/images/greenhouse/relay_pcb.png" alt="drawing" width="400"/>
</p>

The PCB can be seen in the lower right of the electronics canvas. I should also mention that each heater has its own breaker in case of failure.

<p align="center"> 
<img src="/greenhouse/images/greenhouse/IMG_6125.jpeg" alt="drawing" width="400"/>
</p>


## Concluding Thoughts

This works for now but I would like to add in high side current monitoring to the relay board for additional telemetry.









<script>
function calculate_power_loss() {
    var k_glass = Number(document.getElementById("k_glass").value);
    var h_inside = Number(document.getElementById("h_inside").value);
    var h_outside = Number(document.getElementById("h_outside").value);

	var L = 28e-3 // thickness of window 
	var A = 15 //m2 area of window

    var R_cond = L / (k_glass * A)
	var R_conv_i = 1 / (h_inside * A)
	var R_conv_o = 1 / (h_outside * A)
	var R_total =  R_cond + R_conv_i + R_conv_o
	var T_inside = 5
	var T_outside = 0 
	var Q_dot = (T_inside - T_outside) / R_total



    document.getElementById("myText").innerHTML = Math.round(Q_dot).toFixed(2) + "W"

}
</script>


