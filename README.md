# GHDgl

My personal OpenGL sandbox project.
I plan to implement various OpenGL features and techniques in this project.

![demo](demo.png)
Currently tested on Windows 10 (MinGW)

## Dependencies

- CMake 3.29.1 or higher (Could work on older versions)

## Stack

- CMake
- OpenGL
- GLFW3
- GLAD
- GLM
- STB_IMAGE
- IMGUI(Docking)

## Features

- Simple main.cpp hello triangle example
- Color Picker using dearimgui

## TODO

- Add TODO items!

## Build

```bash
$ git clone repo
$ cd GHDgl
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ./GHDgl
```

## Demos

Triangle with vertex color
![tricolor_triangle](demos/tricolor_triangle.png)

Square with EBO
![square_ebo](demos/square_ebo.png)

Simple Texture
![texture](demos/texture.png)

Texture mixed with color
![texture_mixed](demos/texture_mixed.png)

MVP Matrices
![mvp](demos/MVP.png)

Cube
![cube](demos/cube.png)

Rotated Cube
![rotated_cube](demos/rotated_cube.png)

