#include "shader.h"
// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
		std::cout<<"> Shader read: "<<contents<<"\n";
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// TODO: undo this to use file again
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// const char* vertexSource = vertexFile;
	// const char* fragmentSource = fragmentFile;

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	id = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(id);
	// Checks if Shaders linked succesfully
	compileErrors(id, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}


// Activates the Shader Program
void Shader::use()
{
	glUseProgram(id);
}

// Deletes the Shader Program
void Shader::remove()
{
	glDeleteProgram(id);
}

void Shader::uniform_int(const char *name, int v0) {
	int colorUniformLocation = glGetUniformLocation(id, name);
	glUseProgram(id);
	glUniform1i(colorUniformLocation, v0);
}

// Sets a 1f uniform
void Shader::uniform_1f(const char *name, float v0)
{
    int colorUniformLocation = glGetUniformLocation(id, name);
    glUseProgram(id);
    glUniform1f(colorUniformLocation, v0);
}

// Sets a bool uniform
void Shader::uniform_bool(const char *name, bool v0)
{
	int colorUniformLocation = glGetUniformLocation(id, name);
	glUseProgram(id);
	glUniform1i(colorUniformLocation, v0);
}

// Sets a 2f uniform
void Shader::uniform_2f(const char *name, float v0, float v1)
{
    int colorUniformLocation = glGetUniformLocation(id, name);
    glUseProgram(id);
    glUniform2f(colorUniformLocation, v0, v1);
}

// Sets a 3f uniform
void Shader::uniform_3f(const char* name, float v0, float v1, float v2)
{
    int colorUniformLocation = glGetUniformLocation(id, name);
    glUseProgram(id);
    glUniform3f(colorUniformLocation, v0, v1, v2);
}

// Sets a 4f uniform
void Shader::uniform_4f(const char *name, float v0, float v1, float v2, float v3)
{
    int colorUniformLocation = glGetUniformLocation(id, name);
    glUseProgram(id);
    glUniform4f(colorUniformLocation, v0, v1, v2, v3);
}

void Shader::uniform_mat4(const char *name, float *mat4)
{
	int UniformLocation = glGetUniformLocation(id, name);
	glUseProgram(id);
	glUniformMatrix4fv(UniformLocation, 1, GL_FALSE, mat4);
}

#include <glm/glm.hpp> // Include the appropriate header file for the "glm" library

void Shader::uniform_mat4fv(const char *name, const glm::f32* mat4) // Remove the global-scope qualifier "::"
{
	int UniformLocation = glGetUniformLocation(id, name);
	glUseProgram(id);
	glUniformMatrix4fv(UniformLocation, 1, GL_FALSE, mat4);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}