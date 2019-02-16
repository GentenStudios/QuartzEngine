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
