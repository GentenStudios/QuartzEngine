#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/API/gl/GLTexture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;

GLTexture::GLTexture()
{
	GLCheck(glGenTextures(1, &m_id));
}

GLTexture::~GLTexture()
{
	GLCheck(glDeleteTextures(1, &m_id));
}

GLTexture::GLTexture(GLTexture&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_slot = o.m_slot;

	m_flipOnX = o.m_flipOnX;
	m_flipOnY = o.m_flipOnY;

	m_format = o.m_format;
	m_filter = o.m_filter;
	m_wrap = o.m_wrap;
}

GLTexture& GLTexture::operator=(GLTexture&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_slot = o.m_slot;

	m_flipOnX = o.m_flipOnX;
	m_flipOnY = o.m_flipOnY;

	m_format = o.m_format;
	m_filter = o.m_filter;
	m_wrap = o.m_wrap;

	return *this;
}

void GLTexture::setOptions(TextureOptions options)
{
	m_flipOnX = options.flipOnX;
	m_flipOnY = options.flipOnY;

	m_format = gfxToOpenGL(options.format);
	m_filter = gfxToOpenGL(options.filter);
	m_wrap = gfxToOpenGL(options.wrap);
}

void GLTexture::bind(int slot) const
{
	m_slot = slot;

	if (m_slot != -1)
		GLCheck(glActiveTexture(m_slot));

	GLCheck(glBindTexture(GL_TEXTURE_2D, m_id));
}

void GLTexture::unbind() const
{
	if (m_slot != -1)
		GLCheck(glActiveTexture(m_slot));

	GLCheck(glBindTexture(GL_TEXTURE_2D, 0));
}

void GLTexture::setDataFromFile(const std::string& filepath)
{
	int width = -1, height = -1, nbChannels = -1;
	unsigned char* image = stbi_load(filepath.c_str(), &width, &height, &nbChannels, 0);
	if (image != nullptr)
	{
		GLCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, m_format, GL_UNSIGNED_BYTE, image));
	}
	else
	{
		utils::Logger::instance()->log(utils::LogVerbosity::WARNING, __FILE__, __LINE__, "[RENDERING][TEXTURING]", "The texture: ", filepath, " could not be found.");
		return;
	}
	
	stbi_image_free(image);

	GLCheck(glGenerateMipmap(GL_TEXTURE_2D));
	GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap));
	GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap));
	GLCheck(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f));
}

void GLTexture::setDataFromMemory(const void* dataPointer)
{
}
