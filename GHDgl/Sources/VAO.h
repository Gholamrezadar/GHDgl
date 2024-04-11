#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint id;
	
    // Constructor that generates a VAO ID
	VAO();

	// Links a VBO Attribute such as a position or color to the VAO
	void linkAttrib(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	
    // Binds the VAO
	void bind();
	
    // Unbinds the VAO
	void unbind();
	
    // Deletes the VAO
	void remove();
};

#endif