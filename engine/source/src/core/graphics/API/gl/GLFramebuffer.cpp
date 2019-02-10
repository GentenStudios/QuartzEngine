#include <quartz/core/quartz-pch.hpp>
#include <quartz/core/graphics/API/gl/GLFramebuffer.hpp>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;

GLFramebuffer::GLFramebuffer() : m_id(0)
{
}

GLFramebuffer::~GLFramebuffer()
{
}

GLFramebuffer::GLFramebuffer(GLFramebuffer&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;
}

GLFramebuffer& GLFramebuffer::operator=(GLFramebuffer&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	return *this;
}

void GLFramebuffer::bind() const
{
}

void GLFramebuffer::unbind() const
{
}

void GLFramebuffer::reset()
{
}

void GLFramebuffer::getSize(int& x, int& y) const
{
}

ITexture* GLFramebuffer::getTexture() const
{
	return nullptr;
}
