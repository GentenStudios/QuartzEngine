#include <quartz/core/quartz-pch.hpp>
#include <quartz/core/graphics/API/IFramebuffer.hpp>
#include <quartz/core/graphics/API/Context.hpp>
#include <quartz/core/graphics/API/gl/GLFramebuffer.hpp>

using namespace qz::gfx::api;

GraphicsResource<IFramebuffer> IFramebuffer::generateFramebuffer()
{
	switch (Context::getRenderingAPI())
	{
	case RenderingAPI::OPENGL:
		return GraphicsResource<IFramebuffer>(new gl::GLFramebuffer());

	default:
		return nullptr;
	}
}
