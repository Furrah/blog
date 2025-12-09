---
title: "Fungi Identify Neural Network"
date: 2025-12-09T18:10:30+01:00
tags: []
draft: false
---

# There must be a dataset somewhere?

Over the last few years I have been taking photos of almost every mushroom that I've seen but I don't always know what they are. There are many mushroom apps out there now and most of the good ones require some form of subscription. I woke up this morning thinking that there must be a compiled dataset somewhere for fungi, and there is! Hello <a href="https://bohemianvra.github.io/FungiTastic/" target="_blank"> FungiTastic</a>!

# There must be a pre-trained model somewhere?

Ok, brilliant, I've got the dataset, but they must have pre-trained a model already right? They have! hooooray!

# What is this mushroom?

The model was super simple to get working. The only thing i couldn't figure out was how to actually get the species name from the output. I seem to be able to only get the class_id. FungiTastic provide the labelled training dataset so a map between class_id and species was easy enough to generate. I tested it out on a bunch of images I had. Here you can see if predicted that this photo of a Fly Agaric is indeed Amanita muscaria, also known as Fly Agaric with 100% certainty! 

<p align="center"> 
<img src="/misc/images/fungi/fly_agaric/IMG_5224.jpeg" alt="drawing" width="600" loading="lazy"/>
</p>


```
IMG_5224.jpeg → Amanita muscaria    (1.000)
```

# Files 

<a href="/docs/fungi_nn/fungi_nn.zip" download="fungi_nn.zip" class="download-link">
  fungi_nn.zip
  <i data-feather="download" style="margin-left:6px;"></i>
</a>
