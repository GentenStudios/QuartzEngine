#include <quartz/core/quartz-pch.hpp>
#include <quartz/core/graphics/API/ITexture.hpp>
#include <quartz/core/graphics/API/Context.hpp>
#include <quartz/core/graphics/API/gl/GLTexture.hpp>

using namespace qz::gfx::api;

GraphicsResource<ITexture> ITexture::generateTexture(TextureOptions options)
{
	switch (Context::getRenderingAPI())
	{
	case RenderingAPI::OPENGL:
		return GraphicsResource<ITexture>(new gl::GLTexture());

	default:
		return nullptr;
	}
}
