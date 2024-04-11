#ifndef TEXTUREE_H
#define TEXTUREE_H

#include <glad/glad.h>
// #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

class Texturee
{
public:
	GLuint id;
	GLenum type;

	Texturee(const char* image, unsigned int texType, unsigned int slot, unsigned int format, unsigned int pixelType);

	// Binds a texture
	void bind();

	// bind to texture slot "slot" e.g. GL_TEXTURE0
	void bind(unsigned int slot);

	// Unbinds a texture
	void unbind();
	// Deletes a texture
	void remove();
};
#endif