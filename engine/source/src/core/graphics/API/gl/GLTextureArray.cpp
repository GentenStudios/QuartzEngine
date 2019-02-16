#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/API/gl/GLTextureArray.hpp>
#include <quartz/core/graphics/API/gl/GLCommon.hpp>

#include <stb_image.h>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;

GLTextureArray::GLTextureArray()
{
	GLCheck(glGenTextures(1, &m_id));
	bind();
	GLCheck(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 16, 16, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
	unbind();
}

GLTextureArray::~GLTextureArray()
{
	GLCheck(glDeleteTextures(1, &m_id));
}

GLTextureArray::GLTextureArray(GLTextureArray&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_layerNumber = o.m_layerNumber;
	m_texNames = std::move(o.m_texNames);
	m_texReservations = std::move(o.m_texReservations);
}

GLTextureArray& GLTextureArray::operator=(GLTextureArray&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_layerNumber = o.m_layerNumber;
	m_texNames = std::move(o.m_texNames);
	m_texReservations = std::move(o.m_texReservations);

	return *this;
}

void GLTextureArray::setOptions(TextureOptions options)
{
	m_flipOnX = options.flipOnX;
	m_flipOnY = options.flipOnY;

	m_format = gfxToOpenGL(options.format);
	m_filter = gfxToOpenGL(options.filter);
	m_wrap = gfxToOpenGL(options.wrap);
}

void GLTextureArray::add(const std::string& filepath)
{
	bind();

	if (m_texNames.find(filepath) == m_texNames.end())
	{
		int width = -1, height = -1, nbChannels = -1;
		unsigned char* image = stbi_load(filepath.c_str(), &width, &height, &nbChannels, 0);
		if (image != nullptr)
		{
			GLCheck(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_layerNumber, width, height, 1, m_format, GL_UNSIGNED_BYTE, image));

			m_texNames[filepath] = m_layerNumber++;
		}
		else
		{
			qz::Logger::get()->log(LogVerbosity::WARNING, __FILE__, __LINE__, "[RENDERING][TEXTURING]", "The texture: ", filepath, " could not be found.");
			return;
		}

		stbi_image_free(image);

		GLCheck(glGenerateMipmap(GL_TEXTURE_2D_ARRAY));
		GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, m_filter));
		GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, m_wrap));
		GLCheck(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, m_wrap));
		GLCheck(glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f));
	}

	unbind();
}

void GLTextureArray::reserve(const std::string& filepath)
{
	if (m_texReservations.find(filepath) == m_texReservations.end())
	{
		m_texReservations[filepath] = m_layerNumber++;
	}
}

void GLTextureArray::resolveReservations()
{
	bind();

	for (const auto& current : m_texReservations)
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
				qz::Logger::get()->log(LogVerbosity::WARNING, __FILE__, __LINE__, "[RENDERING][TEXTURING]", "The texture: ", current.first, " could not be found.");
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

	m_texReservations.clear();

	unbind();
}

void GLTextureArray::bind(int slot) const
{
	m_slot = slot;
	if (m_slot != -1)
	{
		GLCheck(glActiveTexture(GL_TEXTURE0 + m_slot));
	}

	GLCheck(glBindTexture(GL_TEXTURE_2D_ARRAY, m_id));
}

void GLTextureArray::unbind() const
{
	if (m_slot != -1)
	{
		GLCheck(glActiveTexture(GL_TEXTURE0 + m_slot));
	}

	GLCheck(glBindTexture(GL_TEXTURE_2D_ARRAY, m_id));
}

const TexCache& GLTextureArray::getTextureList() const
{
	return m_texNames;
}

int GLTextureArray::getTexLayer(const std::string& path)
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
