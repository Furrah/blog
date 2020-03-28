---
title: "Rules and Permissions for USB Blaster Setup in Linux Virtual Machine"
date: 2020-03-22T20:14:00Z
tags: []
draft: false
---

SOURCE: https://stackoverflow.com/questions/18704913/unable-to-lock-chain-insufficient-port-permissions


If when jtagconfig is ran 
```bash
1) USB-Blaster varient [2-1]
	unable to lock chain(Insufficient port permissions)
```
is returned and Quartus cant program your FPGA. The following steps should fix this problem. An amazing resource on setting up Quartus and other Altera related design software is
<a href=https://wiki.archlinux.org/index.php/Altera_Design_Software  target="_blank"> Altera Design Software  </a>




Before a USB Blaster can be used its jtag rules and permissions must be configured. 

First kill jtagd.

```bash
sudo killall -9 jtagd
```

If jtagconfig is ran whilst jtagd is already running then jtagconfig will have no effect.
jtagd and jtagconfig can be found in 

```bash
/altera/3.1/quartus/bin 
```
And can be executed using

```bash
./jtagd 
./jtagconfig
```

As root create file /etc/udev/rules.d/51-altera-usb-blaster.rules

Inside the file, include
```bash
SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6001", MODE="0666"
SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6002", MODE="0666"
SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6003", MODE="0666"
SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6010", MODE="0666"
SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6810", MODE="0666"
```

The five idProducts are all the known USB-Blaster Download Cable USB product IDs (for the Altera vendor ID, 0x09fb).


Then run 
```bash
sudo udevadm control --reload
```

Now run jtagd. 
```bash
./jtagd
```

Before jtagconfig returned

1) USB-Blaster varient [2-1]
	unable to lock chain(Insufficient port permissions)

Now, it returns

1) USB-Blaster [2-1]
	020F70DD EP3C120/EP4CE115	


Go to Quartus II and open tools -> programming

In hardware setup the USB Blaster should be found as USB-Blaster and not USB-Blaster varient.


Other useful resources <br>
https://blog.atomminer.com/fighting-altera-usb-blaster-on-ubuntu/
https://rileywood.me/2017/02/19/fpga_setup/




