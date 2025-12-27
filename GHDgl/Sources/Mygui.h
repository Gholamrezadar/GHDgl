#ifndef MYy_GUI_CLASS_H
#define MYy_GUI_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// #include "Texturee.h"
#include "Shader.h"
#include "utils.h"

class MyGUI3
{
public:
    int frameCount = 0;
    double fps = 0.0;
    double previousTime = 0.0;

    float angle = 55.0f;

    unsigned int shadowMap;
    float shadow_bias = 0.001f;
    float near_plane = 0.0f;
    float far_plane = 13.0f;
    float ortho_size = 0.8f;
    glm::vec3* DirLightPos = nullptr; 
    std::vector<std::string> logs;

    glm::vec3 triangleColor = glm::vec3(1.0f, 0.0f, 0.0f);

    MyGUI3();
    void calcFPS(double updateInterval);
    void renderGUI(Shader& flatTextureShader);
    void update(Shader& flatTextureShader);
    void log(std::string message);
    void cleanup();

private:
    void modelRotationUI(Shader & flatTextureShader);
    void colorPickerUI(Shader & flatTextureShader);
    void fpsUI();
    void logUI();
    void shadowMapUI();
};

#endif