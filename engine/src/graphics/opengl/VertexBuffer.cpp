#include "engine/graphics/opengl/VertexBuffer.hpp"

using namespace phx::gfx::gl;

VertexBuffer::VertexBuffer(Target target, Usage usage) : m_target(target), m_usage(usage)
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

void VertexBuffer::addVertexAttrib(int index, int componentCount, int totalSize, int offset)
{
	m_vertexAttribs.push_back({ index, componentCount, totalSize, offset });
}

void VertexBuffer::enableVertexAttribs()
{
	for (auto& attrib : m_vertexAttribs)
	{
		glVertexAttribPointer(
			attrib.index,
			attrib.totalSize,
			GL_FLOAT,
			GL_FALSE,
			attrib.totalSize * sizeof(float),
			(void*)(attrib.offset * sizeof(float))
		);
		glEnableVertexAttribArray(attrib.index);
	}
}
