cmake_minimum_required(VERSION 3.12)
project(GHDgl)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Add glad library
add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)

# Add stb_image library
add_library(stb_image STATIC vendor/stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC vendor/stb_image)


# Header Files
file(GLOB PROJECT_HEADERS GHDgl/Headers/*.h
                        GHDgl/Headers/*.hpp)
# Source Files
file(GLOB PROJECT_SOURCES GHDgl/Sources/*.cpp)
# Shader Files
file(GLOB PROJECT_SHADERS GHDgl/Shaders/*.comp
                        GHDgl/Shaders/*.frag
                        GHDgl/Shaders/*.geom
                        GHDgl/Shaders/*.vert)
# Image Files
file(GLOB PROJECT_IMAGES GHDgl/Media/Images/*.png
                        GHDgl/Media/Images/*.jpg)

# Add the ImGui include directory
include_directories(vendor/imgui)

# Add the ImGui source files
file(GLOB IMGUI_SOURCES vendor/imgui/*.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                            ${PROJECT_SHADERS} ${IMGUI_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad stb_image ${OPENGL_LIBRARIES})

# Copy Shaders into the build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders
    DEPENDS ${PROJECT_SHADERS})

# Copy Images into the build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/Media/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_IMAGES})


