---
title: "CMake Setup"
date: 2020-05-23T21:45:48+02:00
tags: []
draft: true
---

## Installing CMake on macOS and adding to path

Cmake can be installed using 
```bash
brew install cmake
```
if you have the homebrew package manager installed. If not, go to <a href=https://cmake.org/download/ target="_blank">CMake</a> and download the latest version. 

once installed add to path using the command

```bash
sudo /Applications/CMake.app/Contents/bin/cmake-gui --install=/usr/local/bin
```

Done!