#include "engine/graphics/opengl/VertexBuffer.hpp"

using namespace phx::gfx::gl;

VertexBuffer::VertexBuffer(BufferTarget target, BufferUsage usage) : m_target(target), m_usage(usage)
{
	glGenBuffers(1, &m_bufferID);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void VertexBuffer::bind()
{
	glBindBuffer(static_cast<GLenum>(m_target), m_bufferID);
}

void VertexBuffer::unbind()
{
	glBindBuffer(static_cast<GLenum>(m_target), 0);
}

void VertexBuffer::setData(void* buffer, int size)
{
	glBufferData(static_cast<GLenum>(m_target), size, buffer, static_cast<GLenum>(m_usage));
}

void VertexBuffer::subData(void* buffer, int offset, int size)
{
	glBufferSubData(static_cast<GLenum>(m_target), offset, size, buffer);
}

unsigned int VertexBuffer::getID() const
{
	return m_bufferID;
}
