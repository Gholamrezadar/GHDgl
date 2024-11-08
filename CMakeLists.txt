cmake_minimum_required(VERSION 3.12)
project(GHDgl)

# change to Debug for debug build and Release for release build
# set(CMAKE_BUILD_TYPE Release)
# add_compile_options(-O3)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find required packages
find_package(OpenGL REQUIRED)

# Add glfw library
add_subdirectory(vendor/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) # don't build docs
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE) # don't build tests
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build examples

# Add glad library
add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)

# Add stb_image library
add_library(stb_image STATIC vendor/stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC vendor/stb_image)

# Header Files
file(GLOB PROJECT_HEADERS ${PROJECT_NAME}/Headers/*.h
                        ${PROJECT_NAME}/Headers/*.hpp)
# Source Files
file(GLOB PROJECT_SOURCES ${PROJECT_NAME}/Sources/*.cpp)

# Shader Files
file(GLOB PROJECT_SHADERS ${PROJECT_NAME}/Shaders/*.comp
                        ${PROJECT_NAME}/Shaders/*.frag
                        ${PROJECT_NAME}/Shaders/*.geom
                        ${PROJECT_NAME}/Shaders/*.vert)
# Image Files
file(GLOB PROJECT_IMAGES ${PROJECT_NAME}/Media/Images/*.png
                        ${PROJECT_NAME}/Media/Images/*.jpg)

# Add the ImGui include directory
include_directories(vendor/imgui)

# Add the vendor include directory for glm
include_directories(vendor)

# Add the ImGui source files
file(GLOB IMGUI_SOURCES vendor/imgui/*.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                            ${PROJECT_SHADERS} ${IMGUI_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glad stb_image glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})

# Copy Shaders into the build directory
add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders
    DEPENDS ${PROJECT_SHADERS}
)

# Copy Images into the build directory
add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/Media/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_IMAGES}
)


