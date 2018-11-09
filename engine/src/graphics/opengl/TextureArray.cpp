#include "engine/graphics/opengl/TextureArray.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <algorithm>

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

int phx::gfx::gl::TextureArray::getTexLayer(const std::string& path)
{
	if (m_texNames.find(path) != m_texNames.end())
	{
		return m_texNames[path];
	}

	return -1;
}

void TextureArray::add(const std::vector<std::string>& paths)
{
	bind();
	int mipLevelCount = 4;
	auto layerCount = static_cast<GLsizei>(paths.size());
	GLCheck(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 16, 16, layerCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

	for (auto& path : paths) {
		if (m_texNames.find(path) == m_texNames.end())
		{
			RENDER_DEBUG("[TEXTURING]", "TEXTURE NOT FOUND, LOADING...");
			int width, height, nbChannels;
			unsigned char* image = stbi_load(path.c_str(), &width, &height, &nbChannels, 0);
			if (image != nullptr)
			{
				GLCheck(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_textureNumber, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image));
				m_texNames[path] = m_textureNumber;
				m_textureNumber++;
			}
			else
			{
				RENDER_DEBUG("[TEXTURING]", "Image could not be loaded.");
				continue;
			}
			stbi_image_free(image);
		}
	}

	GLCheck(glGenerateMipmap(GL_TEXTURE_2D_ARRAY));
	GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCheck(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f));
	unbind();
}

void TextureArray::add(const std::string& path)
{
	bind();
	int mipLevelCount = 4;
	GLCheck(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 16, 16, static_cast<GLsizei>(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

	if (m_texNames.find(path) == m_texNames.end())
	{
		RENDER_DEBUG("[TEXTURING]", "TEXTURE NOT FOUND, LOADING...");
		int width, height, nbChannels;
		unsigned char* image = stbi_load(path.c_str(), &width, &height, &nbChannels, 0);
		std::cout << width << " " << height << std::endl;
		if (image != nullptr)
		{
			GLCheck(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_textureNumber, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image));
			m_texNames[path] = m_textureNumber;
			m_textureNumber++;
		}
		else
		{
			RENDER_DEBUG("[TEXTURING]", "Image could not be loaded.");
			return;
		}
		stbi_image_free(image);

		GLCheck(glGenerateMipmap(GL_TEXTURE_2D_ARRAY));
		GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCheck(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f));
	}

	unbind();
}