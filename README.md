# GHDgl

My personal OpenGL sandbox project.
I plan to implement various OpenGL features and techniques in this project.

![demo](demo.png)
Currently tested on Windows 10 (Visual Studio 2022)

## Dependencies

- CMake 3.31 or higher
- You need to build assimp.dll and assimp.lib by your own and place them inside `vendor/assimp/lib`
	- also rename them in `CMakeLists.txt` file if needed.

## Stack

- CMake
- OpenGL
- GLFW 3
- GLAD
- GLM
- STB_IMAGE
- IMGUI (Docking)
- ASSIMP

## Features

- Phong Shader
- Multiple Lights
- FPS Camera Movement
- Textures

## TODO

- [ ] Loading Meshes
- [ ] Fresnel Shader
- [ ] Outline Shader
- [ ] Wireframe Shader
- [ ] Refactoring the whole shit

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

17. Multiple Lights

Implemented multiple lights.
![multiple_lights](demos/multi_light.png)

16. Light Attenuation

Implemented light attenuation.
![light_attenuation](demos/light_attenuation.png)

15. Multiple Cubes

Render multiple cubes in a grid.
![multiple_cubes](demos/multiple_cubes.png)

14. Texture Maps

Diffuse and Specular Texture Maps!
![texture_maps](demos/texture_specular.png)


13. Materials

Refactored the shader properties into a Material and Light struct in the fragment shader.
![material](demos/material.png)

12. Specular Lighting

Implemented Specular lighting using Phong lighting model and visualized the light using a second small cube.
![specular](demos/specular.png)

11. Diffuse Lighting

Implemented simple diffuse lighting using Phong lighting model.
![diffuse](demos/diffuse.png)

10. Normal

Added normal vector to the vertex data and implemented simple normal debugger shader.
![normal](demos/normal.png)

9. Camera

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
