#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint id;

	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void use();

	// Deletes the Shader Program
	void remove();

    // Sets a 1f uniform
    void uniform_1f(const char* name, int v0);

    // Sets a 2f uniform
    void uniform_2f(const char* name, float v0, float v1);

    // Sets a 3f uniform
    void uniform_3f(const char* name, float v0, float v1, float v2);

    // Sets a 4f uniform
    void uniform_4f(const char* name, float v0, float v1, float v2, float v3);

private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};


#endif