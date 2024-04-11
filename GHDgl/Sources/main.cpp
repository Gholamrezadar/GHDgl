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

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "utils.h"

const int scr_width = 800;
const int scr_height = 800;

int main()
{
    // Initialization and GLFW window creation
    GLFWwindow* window;
    int flag;
    flag = initialization(window, scr_width, scr_height, "GHDgl");
    if (flag == -1)
        return flag;

    ///////////////////////////// Scene Setup /////////////////////////////

    // flat shader
    Shader flatShader("Shaders/flatShader.vert", "Shaders/flatShader.frag");
    flatShader.use();
    flatShader.uniform_3f("color", 0.0f, 1.0f, 0.0f);

    // Triangle color (is set from color picker and is passed to shader as a uniform)
    glm::vec3 triangleColor(0.0f, 1.0f, 0.0f);
    
    float triangle[] = 
    {
        // coordinates       |        color
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
        0.5f , -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
        0.0f , 0.5f , 0.0f,     0.0f, 0.0f, 1.0f,
    };

    // Vertices coordinates
    GLfloat square[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
        0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
        0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
    };

    // Indices for vertices order
    GLuint square_indices[] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2 // Lower triangle
    };

    // VAO, VBO
    VAO VAO1;
    VAO1.bind();
    VBO VBO1(square, sizeof(square));
    EBO EBO1(square_indices, sizeof(square_indices));

    VAO1.linkAttrib(0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0); // coordinates
    VAO1.linkAttrib(1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float))); // color
    VAO1.linkAttrib(2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float))); // tex coords

    // Unbind stuff
    VBO1.unbind();
    EBO1.unbind();
    VAO1.unbind();

    // Main loop
    int frameNumber = 0;
    while (!glfwWindowShouldClose(window))
    {
        // std::cout << "Frame number: " << frameNumber << "\n";
        
        /////////////////////////////////// Input ///////////////////////////////////

        // Esc key to exit the program
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        /////////////////////////////////// Draw ///////////////////////////////////

        // Clear background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render The Mesh
        flatShader.use();
        VAO1.bind();
        EBO1.bind();
        VBO1.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //////////////////////////////////// UI ////////////////////////////////////

        // Start the ImGui frame
        ImGuiNewFrame();

        // Color picker
        ImGui::Begin("Color Picker");
        if (ImGui::ColorPicker3("Shader Color", glm::value_ptr(triangleColor)))
        {
            flatShader.uniform_3f("color", triangleColor.r, triangleColor.g, triangleColor.b);
        }
        ImGui::End();

        // Render ImGui
        ImGui::Render(); ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        frameNumber++;
    
    } // Main loop end

    // Cleanup and terminate
    VAO1.remove();
    VBO1.remove();
    flatShader.remove();
    ImGuiCleanup();
    glfwTerminate();

    return 0;
}







////////////////////////////////////////////////////////








// #include <iostream>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"


// /* #region shader*/
// // Vertex Shader source code
// const char *vertexShaderSource = R"(
//     #version 330 core
//     layout (location = 0) in vec3 aPos;

//     void main()
//     {
//         gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//     }
// )";
// /* #endregion */

// // Fragment Shader source code
// const char *fragmentShaderSource = R"(
//     #version 330 core
//     out vec4 FragColor;

//     uniform vec3 triangleColor;  // New uniform variable

//     void main()
//     {
//         FragColor = vec4(triangleColor, 1.0f);
//     }
// )";

// // Callback function for handling window resize
// void framebuffer_size_callback(GLFWwindow *window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }

// // Callback function for ImGui color picker
// void ColorPickerCallback(const ImVec4 &color, void *userData)
// {
//     // Cast the userData to the desired data type
//     glm::vec3 *triangleColor = static_cast<glm::vec3 *>(userData);

//     // Update the triangle color
//     triangleColor->r = color.x;
//     triangleColor->g = color.y;
//     triangleColor->b = color.z;
// }

// int main()
// {
//     // Initialize GLFW
//     if (!glfwInit())
//     {
//         std::cerr << "Failed to initialize GLFW" << std::endl;
//         return -1;
//     }

//     // Configure GLFW
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     // Create a GLFW window
//     GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", nullptr, nullptr);
//     if (window == nullptr)
//     {
//         std::cerr << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     // Make the OpenGL context of the window the current one
//     glfwMakeContextCurrent(window);

//     // Initialize GLAD
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     // Set the viewport dimensions
//     int screenWidth, screenHeight;
//     glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//     glViewport(0, 0, screenWidth, screenHeight);

//     // Register framebuffer resize callback
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // Create Vertex Shader
//     GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//     glCompileShader(vertexShader);

//     // Check Vertex Shader compilation status
//     int success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
//         std::cerr << "Failed to compile Vertex Shader:\n"
//                 << infoLog << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     // Create Fragment Shader
//     GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//     glCompileShader(fragmentShader);

//     // Check Fragment Shader compilation status
//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
//         std::cerr << "Failed to compile Fragment Shader:\n"
//                 << infoLog << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     // Create shader program
//     GLuint shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);

//     // Check shader program linking status
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success)
//     {
//         glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
//         std::cerr << "Failed to link shader program:\n"
//                 << infoLog << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     // Uniforms
//     int colorUniformLocation = glGetUniformLocation(shaderProgram, "triangleColor");
//     glUseProgram(shaderProgram);
//     glUniform3f(colorUniformLocation, 0.0f, 1.0f, 0.0f); // Set triangle color to green

//     // Set up vertex data and buffers
//     float vertices[] = {
//         -0.5f, -0.5f, 0.0f,
//         0.5f, -0.5f, 0.0f,
//         0.0f, 0.5f, 0.0f};

//     GLuint VAO, VBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

//     // Initialize ImGui
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO &io = ImGui::GetIO();
//     (void)io;

//     // Setup ImGui platform/renderer bindings
//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init("#version 330 core");

//     // Triangle color
//     glm::vec3 triangleColor(0.0f, 1.0f, 0.0f);

//     // Main loop
//     while (!glfwWindowShouldClose(window))
//     {
//         // Process input
//         if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//             glfwSetWindowShouldClose(window, true);

//         // Clear background
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Render The triangle
//         glUseProgram(shaderProgram);
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 3);

//         // Render UI(imgui)
//         // Start the ImGui frame
//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplGlfw_NewFrame();
//         ImGui::NewFrame();

//         // ImGui window for color picker
//         ImGui::Begin("Color Picker");
//         if (ImGui::ColorPicker3("Triangle Color", glm::value_ptr(triangleColor)))
//         {
//             // If the color picker value changed, update the uniform
//             int colorUniformLocation = glGetUniformLocation(shaderProgram, "triangleColor");
//             glUseProgram(shaderProgram);
//             glUniform3fv(colorUniformLocation, 1, glm::value_ptr(triangleColor));
//         }
//         ImGui::End();

//         // Render ImGui
//         ImGui::Render();
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//         // Check and call events and swap the buffers
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // Cleanup
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteProgram(shaderProgram);

//     // Cleanup ImGui
//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();

//     // Terminate GLFW
//     glfwTerminate();
//     return 0;
// }
