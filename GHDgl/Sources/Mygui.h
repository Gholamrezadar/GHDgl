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
    glm::vec3 triangleColor = glm::vec3(1.0f, 0.0f, 0.0f);
    float angle = 55.0f;
    std::vector<std::string> logs;
    unsigned int shadowMap;
    glm::vec3* DirLightPos = nullptr; 

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

#endif // !MY_GUI_H