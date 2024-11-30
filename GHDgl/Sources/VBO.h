#ifndef VBO_H
#define VBO_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

// Structure to standardize the vertices used in the meshes
struct Vertexee
{
	glm::vec3 position;
	// glm::vec3 normal;
	// glm::vec3 color;
	// glm::vec2 texUV;

	// constructor
	Vertexee(glm::vec3 pos)
	{
		position = pos;
	}
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint id;

	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertexee>& vertices);
	VBO(float vertices[], int size);

	// Binds the VBO
	void bind();
	
    // Unbinds the VBO
	void unbind();
	
    // Deletes the VBO
	void remove();
};

#endif