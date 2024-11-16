#define GLAD_GL_IMPLEMENTATION

#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Texturee.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "utils.h"
#include "mygui.h"

#include "Camera.h"
const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Initialization and GLFW window creation
    GLFWwindow* window;
    int flag;
    flag = initialization(window, SCR_WIDTH, SCR_HEIGHT, "GHDgl sssd");
    if (flag == -1)
        return flag;

    ///////////////////////////// Scene Setup /////////////////////////////

    // Model matrix
    glm::mat4 model = glm::mat4(1.0f);
    // 55 degree rotation along x-axis
    // model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // light matrix
    glm::vec3 lightPos = glm::vec3(0.0f, 0.55f, 0.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::mat4 light_model = glm::mat4(1.0f);
    float lightScale = 0.03f;
    light_model = glm::translate(light_model, lightPos);
    light_model = glm::scale(light_model, glm::vec3(lightScale, lightScale, lightScale));

    // Camera
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 0.1f, 100.0f);
    // camera.Position += glm::vec3(0.0f, 0.0f, 3.0f);
    camera.Position += glm::vec3(1.5f, 1.5f, 1.5f);
    camera.Position += glm::vec3(0.0f, -0.35f, 0.0f);
    camera.Orientation = glm::rotate(camera.Orientation, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camera.Orientation = glm::rotate(camera.Orientation, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // look at the light

    // Box Shader
    Shader currentShader("Shaders/phongShader.vert", "Shaders/phongShader.frag");
    currentShader.use();
    currentShader.uniform_3f("color", 0.0f, 1.0f, 0.0f);
    currentShader.uniform_1f("texture1", 0);
    currentShader.uniform_mat4("model", glm::value_ptr(model));
    currentShader.uniform_3f("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);
    currentShader.uniform_1f("lightIntensity", 1.0f);
    currentShader.uniform_3f("lightPos", lightPos.x, lightPos.y, lightPos.z); // top light
    currentShader.uniform_3f("lightColor", 1.0f, 1.0f, 1.0f);

    // Material settings
    currentShader.uniform_3f("material.ambient", 1.0f, 0.5f, 0.31f);
    currentShader.uniform_3f("material.diffuse", 1.0f, 0.5f, 0.31f);
    currentShader.uniform_3f("material.specular", 0.5f, 0.5f, 0.5f);
    currentShader.uniform_1f("material.shininess", 32.0f);
    currentShader.uniform_3f("light.ambient",  0.4f, 0.4f, 0.4f);
    currentShader.uniform_3f("light.diffuse",  0.85f, 0.85f, 0.85f);
    currentShader.uniform_3f("light.specular", 1.0f, 1.0f, 1.0f);

    camera.Matrix(currentShader); // this is what moves your object

    // light Shader (basic white color shader)
    Shader lightShader("Shaders/flatShader.vert", "Shaders/flatShader.frag");
    lightShader.use();
    lightShader.uniform_3f("color", lightColor.x, lightColor.y, lightColor.z);
    lightShader.uniform_mat4("model", glm::value_ptr(light_model));
    camera.Matrix(lightShader);

    float cube[] = {
        // positions          // colors           // texture coords // normals
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,        0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,        0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,        0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,        0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,        0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,        0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,        0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,        0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,        -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,        -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,        1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,        1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,        0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,        0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,        0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,        0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,        0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,        0.0f,  1.0f,  0.0f
    };

    // Mesh
    VAO VAO1;
    VAO1.bind();
    VBO VBO1(cube, sizeof(cube));
    // EBO EBO1(square_indices, sizeof(square_indices));

    VAO1.linkAttrib(0, 3, GL_FLOAT, 11 * sizeof(float), (void *)0); // coordinates
    VAO1.linkAttrib(1, 3, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float))); // color
    VAO1.linkAttrib(2, 2, GL_FLOAT, 11 * sizeof(float), (void *)(6 * sizeof(float))); // tex coords
    VAO1.linkAttrib(3, 3, GL_FLOAT, 11 * sizeof(float), (void *)(8 * sizeof(float))); // normals

    // Unbind stuff
    VBO1.unbind();
    // EBO1.unbind();
    VAO1.unbind();

    // Texture
    const char* image_address = "Images/container.jpg";
    Texturee container_texture(image_address, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

    MyGUI3 gui;

    // Main loop
    int frameNumber = 0;

    while (!glfwWindowShouldClose(window))
    {
        /////////////////////////////////// Input ///////////////////////////////////

        processInput(window);
        camera.Inputs(window);
        camera.Matrix(currentShader);
        camera.Matrix(lightShader);
        camera.UpdatePositionInShader(currentShader);
        gui.log("Camera position: " + std::to_string(camera.Position.x) + " " + std::to_string(camera.Position.y) + " " + std::to_string(camera.Position.z));

        /////////////////////////////////// Draw ///////////////////////////////////

        // Clear background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // gui.log("glClearColor");
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render The Mesh
        container_texture.bind();
        currentShader.use();
        VAO1.bind();
        // EBO1.bind();
        VBO1.bind();
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // gui.log("Draw");

        // Render the light
        lightShader.use();
        glDrawArrays(GL_TRIANGLES, 0, 36);


        //////////////////////////////////// UI ////////////////////////////////////

        gui.update(currentShader);

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        frameNumber++;

    } // Main loop end

    // Cleanup and terminate
    VAO1.remove();
    VBO1.remove();
    currentShader.remove();
    container_texture.remove();
    gui.cleanup();
    
    glfwTerminate();

    return 0;
}