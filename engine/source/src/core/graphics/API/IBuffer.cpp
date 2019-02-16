#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/API/IBuffer.hpp>
#include <quartz/core/graphics/API/Context.hpp>
#include <quartz/core/graphics/API/gl/GLBuffer.hpp>

using namespace qz::gfx::api;

GraphicsResource<IBuffer> IBuffer::generateBuffer(BufferTarget target, BufferUsage usage)
{
	switch (Context::getRenderingAPI())
	{
	case RenderingAPI::OPENGL:
		return GraphicsResource<IBuffer>(new gl::GLBuffer(target, usage));

	default:
		return nullptr;
	}
}
