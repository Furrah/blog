---
title: "Comparison of Integrated Noise Spectrum of JFET and BJT input Operational Amplifiers"
date: 2019-10-27T19:04:09+01:00
tags: ["DC", "noise", "integrated", "spectrum", "opamps", "OPA227", "JFET", "BJT"]
type: "E"
draft: false
---

Reference material: https://training.ti.com/sites/default/files/docs/Op%20Amp%20Tech%20Overview_0.pdf

When developing precision DC systems BJT transistors are the way to go. Be careful when selecting an op amp based on its datasheet noise characteristics. At DC we are interested in the 1/f noise, which as the name suggests increases as we approach DC. an example is shown below comparing the JFET input OPA827 and the BJT input OPA227.





![Noise](/electronics/images/JFET-vs-BJT-flicker-noise.png)


<p style="text-align: center;"> *Figure1 - CMOS, BJT, and JFET flicker noise*</p>
<br>
The datasheet for each give a noise denity of 3nV/√Hz for the OPA 227 and 4nV/√Hz for the OPA827. Yet, when compared at low frequency, it is clear which amplifier offers better performance.  