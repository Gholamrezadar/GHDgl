#include "Mygui.h"

MyGUI3::MyGUI3()
{
}

void MyGUI3::calcFPS(double updateInterval)
{
    double currentTime = glfwGetTime();
    frameCount++;
    if (currentTime - previousTime >= updateInterval)
    {
        fps = frameCount / (currentTime - previousTime);
        previousTime = currentTime;
        frameCount = 0;
    }
}

void MyGUI3::renderGUI(Shader& flatTextureShader)
{
    // Start the ImGui frame
    ImGuiNewFrame();

    // Color picker
    colorPickerUI(flatTextureShader);

    // a float slider that controls model rotation angle
    modelRotationUI(flatTextureShader);

    // Display FPS
    fpsUI();

    // Display logs
    logUI();
    
    // Display shadow map
    shadowMapUI();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MyGUI3::shadowMapUI()
{
    ImGui::Begin("Shadow Map");
    ImGui::Text("Shadow Map:");
    ImGui::Image((ImTextureID)(intptr_t)shadowMap,
                ImVec2(256, 256), // size
                ImVec2(0, 1),     // flip vertically
                ImVec2(1, 0));
    ImGui::End();
}

void MyGUI3::fpsUI()
{
    ImGui::Begin("FPS");
    ImGui::Text("(%.1f fps)", fps);
    ImGui::End();
}

void MyGUI3::logUI()
{
    ImGui::Begin("Logs");
    for (auto& log : logs)
    {
        ImGui::Text(log.c_str());
    }
    ImGui::End();
}

void MyGUI3::modelRotationUI(Shader & flatTextureShader)
{
// ImGui::Begin("Model Rotation");
//     if (ImGui::SliderFloat("Angle", &angle, 0.0f, 360.0f))
//     {
//         // initital rotation
//         glm::mat4 model = glm::mat4(1.0f);
//         model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

//         model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
//         flatTextureShader.uniform_mat4("model", glm::value_ptr(model));

//         MyGUI3::log("Model rotation angle: " + std::to_string(angle));
//     }
//     ImGui::End();
    ImGui::Begin("Directional Light Position");
    ImGui::DragFloat3("Directional Light Position",
                  glm::value_ptr(*DirLightPos),
                  0.1f); // speed
    ImGui::DragFloat("Bias", &shadow_bias, 0.00001f, 0.0f, 0.006f, "%.6f");
    ImGui::DragFloat("Near plane", &near_plane, 0.1f, 0.0f, 50.0f, "%.3f");
    ImGui::DragFloat("Far plane", &far_plane, 0.1f, 0.0f, 50.0f, "%.3f");
    ImGui::DragFloat("Ortho size", &ortho_size, 0.1f, 0.0f, 50.0f, "%.3f");
    ImGui::End();
}

void MyGUI3::colorPickerUI(Shader & flatTextureShader)
{
ImGui::Begin("Color Picker");
    if (ImGui::ColorPicker3("Shader Color", glm::value_ptr(triangleColor)))
    {
        flatTextureShader.uniform_3f("color", triangleColor.r, triangleColor.g, triangleColor.b);
    }
    ImGui::End();
}

void MyGUI3::update(Shader& flatTextureShader)
{
    calcFPS(0);
    renderGUI(flatTextureShader);
}

void MyGUI3::log(std::string message)
{
    logs.insert(logs.begin(), message);

    // keep the length of logs to 100
    if (logs.size() > 100)
    {
        logs.pop_back();
    }
}

void MyGUI3::cleanup()
{
    ImGuiCleanup();
}
