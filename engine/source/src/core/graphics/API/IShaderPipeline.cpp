#include <quartz/core/quartz-pch.hpp>
#include <quartz/core/graphics/API/IShaderPipeline.hpp>
#include <quartz/core/graphics/API/Context.hpp>
#include <quartz/core/graphics/API/gl/GLShaderPipeline.hpp>

using namespace qz::gfx::api;

GraphicsResource<IShaderPipeline> IShaderPipeline::generateShaderPipeline()
{
	switch (Context::getRenderingAPI())
	{
	case RenderingAPI::OPENGL:
		return GraphicsResource<IShaderPipeline>(new gl::GLShaderPipeline());

	default:
		return nullptr;
	}
}
