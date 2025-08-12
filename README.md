# GHDgl

My personal OpenGL sandbox project.
I plan to implement various OpenGL features and techniques in this project.

![demo](demos/mesh_loading_final.png)
Currently tested on Windows 10 (Visual Studio 2022)

## Dependencies

- CMake 3.31 or higher
- You need to build assimp.dll and assimp.lib by your own and place them inside `vendor/assimp/lib`
. also rename them in `CMakeLists.txt` file if needed.

## Stack

- CMake
- OpenGL
- GLFW 3
- glad
- glm
- stb_image
- imgui (Docking)
- assimp

## Features

- FPS Camera Movement
- Blinn-Phong Shading
- Multiple Point Lights
- Loading Models
- Textures

<!-- ## TODO

- [ ] Fresnel Shader
- [ ] Outline Shader
- [ ] Wireframe Shader
- [ ] Normal Shader
- [ ] Refactoring the whole shit -->

## Build

```bash
git clone repo
cd GHDgl
mkdir build
cd build
cmake ..
cmake --build .
./GHDgl
```

**NOTE**:  Also make sure to build `assimp.dll` and `assimp.lib` for you own system and place it in `GHDgl/vendor/assimp/lib`. if your files have different names, either rename them to match or change the corresponding names in `CMakeLists.txt` file.

## Dev Log

### 25. Made the scene better

Changed some lighting values and tweaked some textures. Also replaced suzanne with smoother one.

![cubes_pile_suzanne_smooth](demos/piles_scene_better_lighting.png)

![cubes_pile_suzanne_smooth](demos/piles_scene_better_lighting_white.png)

### 24. A new Scene (Cubes Pile)

Implemented a new scene with a plane and a bunch of cubes for upcoming examples.

![cubes_pile](demos/piles_scene.png)

![cubes_pile_white](demos/piles_scene_white.png)

Blender viewport for reference (😪):

![cubes_pile_blender](demos/cube_pile_blender_reference.jpg)

![cubes_pile_blender_white](demos/piles_scene_blender_white.png)

### 23. Culling

Implemented culling.

![culling](demos/culling_scene.png)

### 22. Depth Testing

Here is after changing the depth test func to `GL_ALWAYS`. Displaying the fragments based on the order they were drawn.

![depth_testing_always](demos/depth_func_always.png)

### 21. Blinn-Phong Shading

Implemented blinn-phong shading. here is the before after
![comparison](demos/blinn_phong_shading_comparison.jpg)

### 20. Linearize Depth (Depth Visualization)

Convert the non-linear `gl_FragCoord.z` to linear and visualize it. Visit https://github.com/Gholamrezadar/GHDgl/commit/9f066b032e3883c3d11bd801105f39f8600aa53a to view it.

Linear Depth:

![depth_viz](demos/linear_depth.png)

Non-Linear (Raw) Depth:

![raw_depth_viz](demos/nonlinear_depth.png)

### 19. Model Loading Part 2

Fixed the problems + some extra renders
![final_mesh_loading](demos/mesh_loading_final.png)
![normal_shader_mesh](demos/mesh_wireframe.png)
![normal_shader_mesh](demos/mesh_normal_fix.png)

### 18. Model Loading Part 1

Tried to load meshes but vertex attributes had problems! also building assimp and figuring out how to link it took literally 3 days away from my lifespan.
![mesh_loading](demos/mesh_loading.png)

### 17. Multiple Lights

Implemented multiple lights.
![multiple_lights](demos/multi_light.png)

### 16. Light Attenuation

Implemented light attenuation.
![light_attenuation](demos/light_attenuation.png)

### 15. Multiple Cubes

Render multiple cubes in a grid.
![multiple_cubes](demos/multiple_cubes.png)

### 14. Texture Maps

Diffuse and Specular Texture Maps!
![texture_maps](demos/texture_specular.png)

### 13. Materials

Refactored the shader properties into a Material and Light struct in the fragment shader.
![material](demos/material.png)

### 12. Specular Lighting

Implemented Specular lighting using Phong lighting model and visualized the light using a second small cube.
![specular](demos/specular.png)

### 11. Diffuse Lighting

Implemented simple diffuse lighting using Phong lighting model.
![diffuse](demos/diffuse.png)

### 10. Normal

Added normal vector to the vertex data and implemented simple normal debugger shader.
![normal](demos/normal.png)

### 9. Camera

Added camera class and implemented camera movement using keyboard and mouse input.
![camera](demos/camera.png)

### 8. GUI Update

Refactored GUI code into a GUI class
![gui_update](demos/gui_update.png)

### 7. Rotated Cube

![rotated_cube](demos/rotated_cube.png)

### 6. Cube

![cube](demos/cube.png)

### 5. MVP Matrices

![mvp](demos/MVP.png)

### 4. Texture mixed with color

![texture_mixed](demos/texture_mixed.png)

### 3. Simple Texture

![texture](demos/texture.png)

### 2. Square with EBO

![square_ebo](demos/square_ebo.png)

### 1. Triangle with vertex color

![tricolor_triangle](demos/tricolor_triangle.png)
