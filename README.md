# GHDgl

A very simple and barebone opengl starter project using CMake.

![demo](demo.png)
Currently tested on ubuntu 22.04

## Dependencies

- Must have glfw3 installed
- Must have cmake installed

## Stack

- CMake
- OpenGL
- GLFW3
- GLAD
- GLM
- STB_IMAGE
- IMGUI(Docking)

## Features

- Simple CMakeLists.txt
- Media folder for storing assets
- Shader folder for storing shaders
- Simple main.cpp hello triangle example
- Color Picker using dearimgui

## Build

```bash
$ git clone repo
$ cd GHDgl
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./GHDgl
```