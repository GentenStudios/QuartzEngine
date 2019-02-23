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

#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/API/gl/GLBuffer.hpp>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;

GLBuffer::GLBuffer(BufferTarget target, BufferUsage usage) :
	m_target(gfxToOpenGL(target)), m_usage(gfxToOpenGL(usage))
{
	GLCheck(glGenBuffers(1, &m_id));
}

GLBuffer::~GLBuffer()
{
	if (m_id != 0)
		GLCheck(glDeleteBuffers(1, &m_id));
}

GLBuffer::GLBuffer(GLBuffer&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_size = o.m_size;
	m_target = o.m_target;
	m_usage = o.m_usage;
}

GLBuffer& GLBuffer::operator=(GLBuffer&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_size = o.m_size;
	m_target = o.m_target;
	m_usage = o.m_usage;

	return *this;
}

void GLBuffer::bind()
{
	GLCheck(glBindBuffer(m_target, m_id));
}

void GLBuffer::unbind()
{
	GLCheck(glBindBuffer(m_target, 0));
}

void GLBuffer::resize(unsigned int size)
{
	bind();

	GLCheck(glBufferData(m_target, size, nullptr, m_usage));
	m_size = size;
}

void GLBuffer::setData(unsigned int size, const void* data)
{
	bind();
	
	GLCheck(glBufferData(m_target, size, data, m_usage));
	m_size = size;
}

void GLBuffer::releaseDataPointer()
{
	bind();

	GLCheck(glUnmapBuffer(m_target))
}

void* GLBuffer::retrievePointerInternal()
{
	bind();

	return GLCheck(glMapBuffer(m_target, GL_WRITE_ONLY));
}

