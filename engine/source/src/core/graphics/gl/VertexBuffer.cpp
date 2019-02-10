#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/gl/VertexBuffer.hpp>

using namespace qz::gfx::gl;

VertexBuffer::VertexBuffer(BufferTarget target, BufferUsage usage) : m_target(target), m_usage(usage)
{
	GLCheck(glGenBuffers(1, &m_bufferID));
}

VertexBuffer::~VertexBuffer()
{
	GLCheck(glDeleteBuffers(1, &m_bufferID));
}

void VertexBuffer::bind() const
{
	GLCheck(glBindBuffer(static_cast<GLenum>(m_target), m_bufferID));
}

void VertexBuffer::unbind()
{
	GLCheck(glBindBuffer(static_cast<GLenum>(m_target), 0));
}

void VertexBuffer::setData(void* buffer, int size)
{
	GLCheck(glBufferData(static_cast<GLenum>(m_target), size, buffer, static_cast<GLenum>(m_usage)));
	m_size = size;
}

void VertexBuffer::subData(void* buffer, int offset, int size)
{
	GLCheck(glBufferSubData(static_cast<GLenum>(m_target), offset, size, buffer));
}

unsigned int VertexBuffer::getID() const
{
	return m_bufferID;
}

void VertexBuffer::unmapPointer()
{
	bind();

	GLCheck(glUnmapBuffer(static_cast<GLenum>(m_target)));
}

int VertexBuffer::getSize() const
{
	return m_size;
}
