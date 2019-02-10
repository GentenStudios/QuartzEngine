#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/gl/TextureArray.hpp>
#include <quartz/core/graphics/gl/GLDebug.hpp>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace qz::gfx::gl;

TextureArray::TextureArray()
{
	GLCheck(glGenTextures(1, &m_textureID));
	bind();
	GLCheck(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 16, 16, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
	unbind();
}

TextureArray::~TextureArray()
{
	GLCheck(glDeleteTextures(1, &m_textureID));
}

void TextureArray::bind(int index) const
{
	if (index != -1)
	{
		GLCheck(glActiveTexture(GL_TEXTURE0 + index));
	}

	GLCheck(glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureID));
}

void TextureArray::unbind() const
{
	GLCheck(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
}

const TexCache& TextureArray::getTextureList() const
{
	return m_texNames;
}

int TextureArray::getTexLayer(const std::string& path)
{
	auto it = m_texNames.find(path);
	if (it == m_texNames.end())
	{
		auto it2 = m_texReservations.find(path);
		if (it2 == m_texReservations.end())
			return -1;

		return it2->second;
	}
	return it->second;
}

int TextureArray::getCurrentLayer() const
{
	return m_textureNumber;
}

void TextureArray::add(const std::string& path)
{
	bind();

	if (m_texNames.find(path) == m_texNames.end())
	{
		int width = -1, height = -1, nbChannels = -1;
		unsigned char* image = stbi_load(path.c_str(), &width, &height, &nbChannels, 0);
		if (image != nullptr)
		{
			GLCheck(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_textureNumber, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image));

			m_texNames[path] = m_textureNumber++;
		}
		else
		{
			RENDER_DEBUG("[TEXTURING]", "Image '" + path + "' could not be loaded.");
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

void TextureArray::add(const TexCache& texList)
{
	bind();

	for (const auto& current : texList)
	{
		if (m_texNames.find(current.first) == m_texNames.end())
		{
			int width = -1, height = -1, nbChannels = -1;
			unsigned char* image = stbi_load(current.first.c_str(), &width, &height, &nbChannels, 0);
			if (image != nullptr)
			{
				GLCheck(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, current.second, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image));

				m_texNames[current.first] = current.second;
			}
			else
			{
				RENDER_ERROR("[TEXTURING]", "Image '" + current.first + "' could not be loaded.");
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
	}

	unbind();
}
