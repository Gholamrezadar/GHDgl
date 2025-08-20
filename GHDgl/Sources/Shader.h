#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <glm/glm.hpp> // Include the appropriate header file for the "glm" library


std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint id;

	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);
	Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile);

	// Activates the Shader Program
	void use();

	// Deletes the Shader Program
	void remove();

	// Sets a 1i uniform
	void uniform_int(const char* name, int v0);

    // Sets a 1f uniform
    void uniform_1f(const char* name, float v0);

	// Sets a bool uniform
	void uniform_bool(const char* name, bool v0);

    // Sets a 2f uniform
    void uniform_2f(const char* name, float v0, float v1);

    // Sets a 3f uniform
    void uniform_3f(const char* name, float v0, float v1, float v2);

    // Sets a 4f uniform
    void uniform_4f(const char* name, float v0, float v1, float v2, float v3);

	// sets a 4D matrix
	void uniform_mat4(const char* name, float* mat4);
	void uniform_mat4fv(const char* name, const glm::f32* mat4);

private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};


#endif