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
#include <quartz/core/graphics/API/gl/GLStateManager.hpp>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;

GLStateManager::GLStateManager() : m_id(0)
{
	glGenVertexArrays(1, &m_id);
}

GLStateManager::~GLStateManager()
{
	if (m_id != 0)
		glDeleteVertexArrays(1, &m_id);
}

GLStateManager::GLStateManager(GLStateManager&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_buffers = o.m_buffers;
}

GLStateManager& GLStateManager::operator=(GLStateManager&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_buffers = std::move(o.m_buffers);

	return *this;
}

void GLStateManager::bind() const
{
	GLCheck(glBindVertexArray(m_id));
}

void GLStateManager::unbind() const
{
	GLCheck(glBindVertexArray(0));
}

GraphicsResource<IBuffer> GLStateManager::retrieveBuffer(unsigned index)
{
	if (index < m_buffers.size())
	{
		return m_buffers[index];
	}

	return m_buffers[0];
}

void GLStateManager::attachBuffer(GraphicsResource<IBuffer> buffer)
{
	bind();
	buffer->bind();
	unbind();

	m_buffers.emplace_back(buffer);
}

void GLStateManager::attachBufferLayout(const BufferLayout& bufferLayout, GraphicsResource<IShaderPipeline> shader)
{
	bind();

	m_buffers[0]->bind();

	for (auto& shrek : bufferLayout.getLayouts())
	{
		const int index = shader->retrieveAttributeLocation(shrek.name);

		glVertexAttribPointer(index, 
			shrek.elementCount, 
			gfxToOpenGL(shrek.type), 
			shrek.normalised ? GL_TRUE : GL_FALSE, 
			shrek.countTillNextElement, 
			reinterpret_cast<void*>(shrek.offset));

		glEnableVertexAttribArray(index);
		}

	unbind();
}

void GLStateManager::render(unsigned int start, unsigned int count) const
{
	bind();

	GLCheck(glDrawArrays(GL_TRIANGLES, start, count));

	unbind();
}

