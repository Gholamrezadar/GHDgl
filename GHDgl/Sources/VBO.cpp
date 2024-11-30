#include"VBO.h"
#include <iostream>

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(std::vector<Vertexee>& vertices)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertexee), vertices.data(), GL_STATIC_DRAW);
}

VBO::VBO(float vertices[], int size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

// Unbinds the VBO
void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::remove()
{
	glDeleteBuffers(1, &id);
}