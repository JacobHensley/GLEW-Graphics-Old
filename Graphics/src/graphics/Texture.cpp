#include "Texture.h"
#include "stb_image.h"
#include "GLFW\glfw3.h"

Texture::Texture()
{
	
}

Texture::Texture(const char* path)
	:	path(path)	{
	load();
}

void Texture::load()
{
	int width, height, bpc;
	byte* data = stbi_load(path, &width, &height, &bpc, 0);
	ASSERT(data);

	uint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}
