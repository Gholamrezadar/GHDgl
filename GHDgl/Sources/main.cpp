#define GLAD_GL_IMPLEMENTATION

#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Texturee.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "utils.h"
#include "Mygui.h"
#include "Mesh.h"
#include "Model.h"


#include "Camera.h"
const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;

const int NR_POINT_LIGHTS = 4;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


glm::vec3 pointLightPositions[] = {
    glm::vec3(0.45, 0.55f, 0.0f),
    glm::vec3(-0.45, 0.55f, 0.0f),
    glm::vec3(0.0, 0.55f, 0.45f),
    glm::vec3(0.0, 0.55f, -0.45f),
};

glm::vec3 pointLightColors[] = {
    glm::vec3(0.1f, 0.1f, 0.85f), // blue
    glm::vec3(0.85f, 0.1f, 0.1f)*1.0f, // red
    glm::vec3(0.85f, 0.85f, 0.85f), // white
    glm::vec3(0.1f, 0.85f, 0.1f), // green
};

int main()
{
    //Assimp::Importer importer;
    // Initialization and GLFW window creation
    GLFWwindow* window;
    int flag;
    flag = initialization(window, SCR_WIDTH, SCR_HEIGHT, "GHDgl");
    if (flag == -1)
        return flag;

    ///////////////////////////// Scene Setup /////////////////////////////

    // Model matrix
    glm::mat4 model = glm::mat4(1.0f);

    // Camera
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 0.1f, 100.0f);
    // camera.Position += glm::vec3(0.0f, 0.0f, 3.0f);
    camera.Position += glm::vec3(1.5f, 1.5f, 1.5f);
    camera.Position += glm::vec3(0.0f, -0.35f, 0.0f);
    camera.Orientation = glm::rotate(camera.Orientation, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camera.Orientation = glm::rotate(camera.Orientation, glm::radians(-35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // look at the light

    // Box Shader
    Shader currentShader("Shaders/texturedPhongShader.vert", "Shaders/texturedPhongShader.frag");
    // Shader currentShader("Shaders/depthShader.vert", "Shaders/depthShader.frag");
    currentShader.use();
    currentShader.uniform_3f("color", 0.0f, 1.0f, 0.0f);
    // currentShader.uniform_1f("texture1", 0);
    currentShader.uniform_mat4("model", glm::value_ptr(model));
    currentShader.uniform_3f("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

    // Light settings
    currentShader.uniform_3f("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
    currentShader.uniform_1f("pointLights[0].constant", 1.0f);
    currentShader.uniform_1f("pointLights[0].linear", 0.3f);
    currentShader.uniform_1f("pointLights[0].quadratic", 0.44f);
    currentShader.uniform_3f("pointLights[0].ambient",  0.4f, 0.4f, 0.4f);
    currentShader.uniform_3f("pointLights[0].diffuse",  pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
    currentShader.uniform_3f("pointLights[0].specular", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);

    currentShader.uniform_3f("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
    currentShader.uniform_1f("pointLights[1].constant", 1.0f);
    currentShader.uniform_1f("pointLights[1].linear", 0.3f);
    currentShader.uniform_1f("pointLights[1].quadratic", 0.44f);
    currentShader.uniform_3f("pointLights[1].ambient",  0.0f, 0.0f, 0.0f); // only the first light has ambient
    currentShader.uniform_3f("pointLights[1].diffuse",  pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
    currentShader.uniform_3f("pointLights[1].specular",  pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);

    currentShader.uniform_3f("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
    currentShader.uniform_1f("pointLights[2].constant", 1.0f);
    currentShader.uniform_1f("pointLights[2].linear", 0.3f);
    currentShader.uniform_1f("pointLights[2].quadratic", 0.44f);
    currentShader.uniform_3f("pointLights[2].ambient",  0.0f, 0.0f, 0.0f); // only the first light has ambient
    currentShader.uniform_3f("pointLights[2].diffuse",  pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
    currentShader.uniform_3f("pointLights[2].specular",  pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);

    currentShader.uniform_3f("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
    currentShader.uniform_1f("pointLights[3].constant", 1.0f);
    currentShader.uniform_1f("pointLights[3].linear", 0.3f);
    currentShader.uniform_1f("pointLights[3].quadratic", 0.44f);
    currentShader.uniform_3f("pointLights[3].ambient",  0.0f, 0.0f, 0.0f); // only the first light has ambient
    currentShader.uniform_3f("pointLights[3].diffuse",  pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
    currentShader.uniform_3f("pointLights[3].specular",  pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);

    // Material settings
    currentShader.uniform_3f("material.ambient", 1.0f, 0.5f, 0.31f);
    currentShader.uniform_int("material.diffuse", 0); // set to texture unit 0
    currentShader.uniform_int("material.specular", 1);
    currentShader.uniform_1f("material.shininess", 64.0f);

    camera.Matrix(currentShader); // this is what moves your object

    // light Shader (basic white color shader)
    Shader lightShader("Shaders/flatShader.vert", "Shaders/flatShader.frag");
    // Shader lightShader("Shaders/depthShader.vert", "Shaders/depthShader.frag");

    // I had to change this to position,normal,uv,color using google sheets!
    float cube[] = {
        // positions          // colors           // texture coords // normals
        -0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
- 0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
- 0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
- 0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
- 0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
- 0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
- 0.5f,0.5f,0.5f,-1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
- 0.5f,0.5f,-0.5f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
- 0.5f,-0.5f,-0.5f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
- 0.5f,-0.5f,-0.5f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
- 0.5f,-0.5f,0.5f,-1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
- 0.5f,0.5f,0.5f,-1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,0.5f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,-0.5f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
0.5f,-0.5f,0.5f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,0.5f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
- 0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
- 0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
- 0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
- 0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
- 0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
- 0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
    };

    // Mesh
    VAO VAO1;
    VAO1.bind();
    VBO VBO1(cube, sizeof(cube));

    VAO1.linkAttrib(0, 3, GL_FLOAT, 11 * sizeof(float), (void *)0); // coordinates
    VAO1.linkAttrib(1, 3, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float))); // color
    VAO1.linkAttrib(2, 2, GL_FLOAT, 11 * sizeof(float), (void *)(6 * sizeof(float))); // tex coords
    VAO1.linkAttrib(3, 3, GL_FLOAT, 11 * sizeof(float), (void *)(8 * sizeof(float))); // normals

    // Unbind stuff
    VBO1.unbind();
    VAO1.unbind();

    // Texture
    const char* container2_image_address = "Images/container2.png";
    Texturee container_texture(container2_image_address, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    const char* container2_specular_image_address = "Images/container2_specular.png";
    Texturee container_specular_texture(container2_specular_image_address, GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

    const char* white_image_address = "Images/white.png";
    Texturee white_texture(white_image_address, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    const char* white_specular_image_address = "Images/white_specular.png";
    Texturee white_specular_texture(white_specular_image_address, GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

    MyGUI3 gui;

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_ALWAYS);
    // glDisable(GL_DEPTH_TEST);

    // load models
    // -----------
    Model ourModel("Models/suzanne.obj");
    //Model ourModel("C:\\Users\\ghd\\Downloads\\backpack\\backpack.obj");


    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // Main loop
    int frameNumber = 0;
    glm::vec3 oldCameraPos = camera.Position;
    glm::vec3 oldCameraOrient = camera.Orientation;
    while (!glfwWindowShouldClose(window))
    {
        /////////////////////////////////// Input ///////////////////////////////////
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        camera.Inputs(window);
        camera.Matrix(currentShader);
        camera.Matrix(lightShader);
        camera.UpdatePositionInShader(currentShader);
        
        // Detect camera move
        if(camera.Position != oldCameraPos || camera.Orientation != oldCameraOrient) {
            gui.log("Camera orientation: " + std::to_string(camera.Orientation.x) + " " + std::to_string(camera.Orientation.y) + " " + std::to_string(camera.Orientation.z));
            gui.log("Camera position: " + std::to_string(camera.Position.x) + " " + std::to_string(camera.Position.y) + " " + std::to_string(camera.Position.z));
        }

        /////////////////////////////////// Draw ///////////////////////////////////

        // Clear background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // gui.log("glClearColor");
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render The Scene 
        container_texture.bind(GL_TEXTURE0);
        container_specular_texture.bind(GL_TEXTURE1);
        currentShader.use();
        VAO1.bind();
        VBO1.bind();

        // draw a grid of cubes on the ground
        float gap = 0.04f;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                // change the model matrix to move the cube to the correct position
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(i * (1.0f+gap), 0.0f, j * (1.0f+gap)));
                currentShader.use();
                currentShader.uniform_mat4("model", glm::value_ptr(model));
                camera.Matrix(currentShader);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        // gui.log("Draw");

        // Render the lights
        const float lightScale = 0.03f;
        for(int i=0; i<NR_POINT_LIGHTS; i++) {
            // light matrix
            glm::vec3 lightPos = pointLightPositions[i];
            glm::vec3 lightColor = pointLightColors[i];
            glm::mat4 light_model = glm::mat4(1.0f);
            light_model = glm::translate(light_model, lightPos);
            light_model = glm::scale(light_model, glm::vec3(lightScale, lightScale, lightScale));
            lightShader.use();
            lightShader.uniform_3f("color", pointLightColors[i].x, pointLightColors[i].y, pointLightColors[i].z);
            lightShader.uniform_mat4("model", glm::value_ptr(light_model));
            camera.Matrix(lightShader);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // render the loaded model
        white_texture.bind(GL_TEXTURE0);
        white_specular_texture.bind(GL_TEXTURE1);
        currentShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        currentShader.uniform_mat4("model", glm::value_ptr(model));
        camera.Matrix(currentShader);
        ourModel.Draw(currentShader);

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
    container_specular_texture.remove();
    white_texture.remove();
    white_specular_texture.remove();
    
    gui.cleanup();
    glfwTerminate();

    return 0;
}