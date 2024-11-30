#include"VAO.h"
#include <iostream>

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &id);
}

// Links a VBO Attribute such as a position or color to the VAO
void VAO::linkAttrib(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
}

// Binds the VAO
void VAO::bind()
{
	// std::cout<<id;
	glBindVertexArray(id);
}

// Unbinds the VAO
void VAO::unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::remove()
{
	glDeleteVertexArrays(1, &id);
}