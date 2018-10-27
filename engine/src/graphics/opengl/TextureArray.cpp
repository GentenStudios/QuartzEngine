#include "engine/graphics/opengl/TextureArray.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace phx::gfx::gl;

TextureArray::TextureArray()
{
	GLCheck(glGenTextures(1, &m_textureID));
}

TextureArray::~TextureArray()
{
	GLCheck(glDeleteTextures(1, &m_textureID));
}

void TextureArray::bind(int index)
{
	if (index != -1)
		GLCheck(glActiveTexture(GL_TEXTURE0 + index));
	GLCheck(glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureID));
}

void TextureArray::unbind()
{
	GLCheck(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
}

void TextureArray::add(std::vector<std::string> paths)
{
	bind();
	int mipLevelCount = 4;
	auto layerCount = static_cast<GLsizei>(paths.size());
	GLCheck(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 16, 16, layerCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

	for (auto& path : paths) {
		int width, height, nbChannels;
		unsigned char* image = stbi_load(path.c_str(), &width, &height, &nbChannels, 0);
		if (image == nullptr) std::cout << "Failed to load texture" << std::endl;
		GLCheck(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_textureNumber, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image));
		m_textureNumber++;
		stbi_image_free(image);
	}

	GLCheck(glGenerateMipmap(GL_TEXTURE_2D_ARRAY));
	GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCheck(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f));
	unbind();
}
