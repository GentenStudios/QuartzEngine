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
