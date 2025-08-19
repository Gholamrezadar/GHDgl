#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <imgui.h>
#include <vector>
#include <string>

// Callback function for handling window resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// Callback function for ImGui color picker
void ColorPickerCallback(const ImVec4 &color, void *userData);

int initialization(GLFWwindow*& window, int width, int height, const char* title, int msaa);

void embraceTheDarkness();

ImGuiIO& initializeImGui(GLFWwindow* window);

void ImGuiNewFrame();

void ImGuiCleanup();

unsigned int loadCubemap(std::vector<std::string> faces);

#endif