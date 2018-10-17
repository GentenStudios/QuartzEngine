#include "engine/graphics/opengl/buffer.hpp"

using namespace phoenix::graphics::opengl;

Buffer::Buffer(Target target, Usage usage) : m_target( target ), m_usage( usage )
{
	glGenBuffers( 1, &m_bufferID );
}

Buffer::~Buffer()
{
	glDeleteBuffers( 1, &m_bufferID );
}

void Buffer::bind()
{
	glBindBuffer( static_cast<GLenum>(m_target), m_bufferID );
}

void Buffer::unbind()
{
	glBindBuffer( static_cast<GLenum>(m_target), 0 );
}

void Buffer::setData(void* buffer, int size)
{
	glBufferData( static_cast<GLenum>(m_target), size, buffer, static_cast<GLenum>(m_usage) );
}

void Buffer::subData(void* buffer, int offset, int size)
{
	glBufferSubData( static_cast<GLenum>(m_target), offset, size, buffer );
}

GLuint Buffer::getID() const
{
	return m_bufferID;
}
