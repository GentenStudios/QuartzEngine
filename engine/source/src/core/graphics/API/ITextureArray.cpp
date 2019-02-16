#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/API/ITextureArray.hpp>
#include <quartz/core/graphics/API/Context.hpp>
#include <quartz/core/graphics/API/gl/GLTextureArray.hpp>

using namespace qz::gfx::api;

GraphicsResource<ITextureArray> ITextureArray::generateTextureArray()
{
	switch (Context::getRenderingAPI())
	{
	case RenderingAPI::OPENGL:
		return GraphicsResource<ITextureArray>(new gl::GLTextureArray());

	default:
		return nullptr;
	}
}
