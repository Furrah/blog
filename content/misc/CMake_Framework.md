---
title: "Python script for CMake Framework"
date: 2021-01-17T16:49:22+01:00
tags: []
draft: false
---

## Outline 

* Generate file structure for program architecture.
* Generate generic CMakeLists.txt file for program compilation.
* Generate shell files to run CMake and execute program. 





## File Structure 

The file structure should be 
```
Project_name
|--src
|--|--CMakeLists.txt
|--build
|--|--build.sh
|--run 
|--|--run.sh
```

## Python Script 

```python
#!/usr/local/bin/python3

import os, sys, subprocess 
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-p', action='store', dest='project_name',
                    help='Name of project')

results = parser.parse_args()

if not os.path.exists("./build"):
	os.makedirs("build")

if not os.path.exists("./run"):
	os.makedirs("run")

if not os.path.exists("./src"):
	os.makedirs("src")

os.chdir("src/")

if len(sys.argv) <=1:
	print("Not enough arguments, use -p to add project name")
	sys.exit()

PROJECT_NAME = results.project_name

with open("CMakeLists.txt", 'w+') as file:
	
	file.write("cmake_minimum_required(VERSION 3.18.4)\n\n")
	file.write("project(" + PROJECT_NAME + ")\n\n")
	file.write("add_executable(${PROJECT_NAME} main.cpp)\n\n")
	file.write("add_subdirectory()\n\n")
	file.write("target_include_directories(${PROJECT_NAME}\n\t#/usr/local/include\n\t)\n\n")
	file.write("target_link_directories(${PROJECT_NAME}\n\t#/usr/local/lib\n\t)\n\n")
	file.write("target_link_libraries(${PROJECT_NAME})\n\n")

os.chdir("../run")

with open("run.sh", 'w+') as file:
	file.write("#!/bin/sh\n\n./../build/"+ PROJECT_NAME )

subprocess.run(["chmod","+x", "run.sh"])

os.chdir("../build")

with open("build.sh", 'w+') as file:
	file.write("#!/bin/sh\n\ncmake -S ../src -B .")

subprocess.run(["chmod","+x", "build.sh"])	
```

## Make file executable system wide

Save the python script in a folder of your choice. I've called mine "cmf" - CMakeFramework

navigate to the script and make it executable with 

```bash
chmod +x cmf
```

Then add to path by editing .bashrc/.zshrc or whatever shell you use.

```bash
export PATH=$PATH:<path_to_script>
```

## CMakeLists.txt file

below is the contents of the CMakeLists.txt file for a project called "Test_Project" This can be easily edited and just provides a simple framework for getting started with a C++ project.

```
cmake_minimum_required(VERSION 3.18.4)

project(Test_Project)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory()

target_include_directories(${PROJECT_NAME}
        #/usr/local/include
        )

target_link_directories(${PROJECT_NAME}
        #/usr/local/lib
        )

target_link_libraries(${PROJECT_NAME})
```

## run.sh & build.sh

Generated Shell files

### run.sh 

```
#!/bin/sh

./../build/SneezyJoe
```

### build.sh

```
#!/bin/sh

cmake -S ../src -B .
```

