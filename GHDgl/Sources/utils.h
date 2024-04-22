#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <imgui.h>

// Callback function for handling window resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// Callback function for ImGui color picker
void ColorPickerCallback(const ImVec4 &color, void *userData);

int initialization(GLFWwindow*& window, int width, int height, const char* title);

void embraceTheDarkness();

ImGuiIO& initializeImGui(GLFWwindow* window);

void ImGuiNewFrame();

void ImGuiCleanup();




#endif