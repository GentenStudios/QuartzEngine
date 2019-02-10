#include <quartz/core/quartz-pch.hpp>
#include <quartz/core/graphics/API/IStateManager.hpp>
#include <quartz/core/graphics/API/Context.hpp>
#include <quartz/core/graphics/API/gl/GLStateManager.hpp>

using namespace qz::gfx::api;

GraphicsResource<IStateManager> IStateManager::generateStateManager()
{
	switch (Context::getRenderingAPI())
	{
	case RenderingAPI::OPENGL:
		return GraphicsResource<IStateManager>(new gl::GLStateManager());

	default:
		return nullptr;
	}
}
