// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#include <Quartz/Core/QuartzPCH.hpp>
#include <Quartz/Core/Graphics/API/GL/GLTexture.hpp>

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

