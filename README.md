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

15. Light Attenuation

Implemented light attenuation.
![light_attenuation](demos/light_attenuation.png)

14. Multiple Cubes

Render multiple cubes in a grid.
![multiple_cubes](demos/multiple_cubes.png)

13. Texture Maps

Diffuse and Specular Texture Maps!
![texture_maps](demos/texture_specular.png)


12. Materials

Refactored the shader properties into a Material and Light struct in the fragment shader.
![material](demos/material.png)

11. Specular Lighting

Implemented Specular lighting using Phong lighting model and visualized the light using a second small cube.
![specular](demos/specular.png)

10. Diffuse Lighting

Implemented simple diffuse lighting using Phong lighting model.
![diffuse](demos/diffuse.png)

9. Normal

Added normal vector to the vertex data and implemented simple normal debugger shader.
![normal](demos/normal.png)

8. Camera

Added camera class and implemented camera movement using keyboard and mouse input.
![camera](demos/camera.png)

8. GUI Update

Refactored GUI code into a GUI class
![gui_update](demos/gui_update.png)

7. Rotated Cube

![rotated_cube](demos/rotated_cube.png)

6. Cube

![cube](demos/cube.png)

5. MVP Matrices

![mvp](demos/MVP.png)

4. Texture mixed with color

![texture_mixed](demos/texture_mixed.png)

3. Simple Texture

![texture](demos/texture.png)

2. Square with EBO

![square_ebo](demos/square_ebo.png)

1. Triangle with vertex color

![tricolor_triangle](demos/tricolor_triangle.png)
