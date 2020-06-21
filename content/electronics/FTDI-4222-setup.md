---
title: Interfacing with FTDIs FT4222H USB 2.0 to Quad SPI / I2C Bridge IC
date: 2020-05-23T17:20:32+02:00
tags: []
draft: false
---

A tutorial for interfacing with FTDIs FT4222H USB 2.0 to Quad SPI / I2C Bridge IC on macOS


## Setup

Download the relevent drivers for the IC

D2XX Drivers: <a href=https://www.ftdichip.com/Drivers/D2XX.htm target="_blank">FTD2XX</a>

FT4222H Driver: <a href=https://www.ftdichip.com/Products/ICs/FT4222H.html target="_blank">FT4222H</a>


1. Open D2XX1.4.16.dmg and copy the D2XX folder to your desktop 
2. Inside we are interested in 3 files:

 * ftd2xx.h 
 * WinTypes.h
 * libftd2xx.1.14.16.dylib 

3. Open a terminal and navigate to the D2XX folder on your desktop
4. Move .h files to /usr/local/include 
```bash
mv ftd2xx.h WinTypes.h /usr/local/include 
```
5. Move '.dylib' file to /usr/local/lib
```bash
mv libftd2xx.1.14.16.dylib /usr/local/lib 
```
6. Create second folder on Desktop and copy contents of libft4222.1.4.4.14.dmg to it
7. move ```libft4222.1.4.4.14.dylib``` to /usr/local/lib 
8. move files ```libboost_system.dylib``` and ```libboost_thread-mt.dylib``` located in boost_libs to /usr/local/lib
9. move ```libft4222.h``` to /usr/local/include 
10. Create symbolic links for `libft4222.1.4.4.14.dylib` and ```libftd2xx.1.4.16.dylib```
```bash
sudo -ln -sf /usr/local/lib/libft4222.1.4.4.14.dylib /usr/local/lib/libft4222.dylib
sudo -ln -sf /usr/local/lib/libftd2xx.1.4.16.dylib /usr/local/lib/libftd2xx.dylib
```

#### Notes on installing 
If using a device with standard FTDI vendor and product identifiers, install D2xxHelper to prevent mac OS from claiming the device as a serial port (locking out D2XX programs). This will prevent the device being used with the VCP driver as a standard COM port. D2xxHelper can be found here : <a href=https://www.ftdichip.com/Drivers/D2XX/MacOSX/D2xxHelper_v2.0.0.pkg target="_blank">D2xxHelper</a>

## Testing 

#### 1. Find chip version

Inside libft4222.1.4.4.14.dmg is a folder called examples with a .c file called ```get-version.c```.
using the following command 

```bash
cc get-version.c -lft4222 -lftd2xx  -Wl,-L/usr/local/lib -o version.out
```

If compilation has gone well and all libraries have been found ```version.out``` will have been made.
execute using 
```bash 
./version.out
```

This should return something similar to this 
```bash 
Device 0: 'FT4222 A'
  Chip version: 42220400, LibFT4222 version: 01040409
```

### 2. Accessing EEPROM

Create a folder in the root directory of D2XX called ```build``` and move ```libftd2xx.a``` into it.
```bash
mkdir build
mv libftd2xx.a build
```
now navigate to the folder ```Samples```

Inside the D2XX folder navigate to the folder samples and execute ```make```
```bash
make
```

once this has complete navigate to D2XX/Samples/EEPROM/read and exectute read
```bash
./read
```

This should return something similar to this 
```bash
Signature1 = 0
Signature2 = -1
Version = 0
VendorId = 0x0403
ProductId = 0x601C
Manufacturer = FTDI
ManufacturerId =
Description = FT4222
SerialNumber =
MaxPower = 100
PnP = 1
SelfPowered = 0
RemoteWakeup = 1
Returning 0
```
### 3. Using Cmake


Navigate to the examples folder as before containing ```get-version.c```<br>
Create a directory called ```build```



create a text file called ```CMakeLists.txt```

Inside add the following 

```html
cmake_minimum_required(VERSION 3.17.2)

project (FT4222H_test)

set ( PROJECT_LINK_LIBS libft4222.dylib libftd2xx.dylib )
link_directories ( ~/work/CERN/FTDI/example/build /usr/local/lib)

include_directories ( /usr/local/include )

add_executable( FT4222H_Version get-version.c ) 
target_link_libraries( FT4222H_Version ${PROJECT_LINK_LIBS} )
```

This tells the compiler where to find our files and links them to the project.<br>
Inside link directories replace the first directory with the location of your build folder.
Navigate to the build folder and run 

```bash
cmake ..
make
```

The file ``` FT4222H_Version ``` should now be built.

execute with 
```bash
./FT4222H_Version
```

Again, the following should be returned 

```bash
Device 0: 'FT4222 A'
  Chip version: 42220400, LibFT4222 version: 01040409
```














