#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/IWindow.hpp>
#include <quartz/core/platform/GLWindow.hpp>

using namespace qz::gfx;

IWindow* IWindow::create(const std::string& title, const unsigned int width, const unsigned int height, std::size_t flags, RenderingAPI renderingAPI)
{
	Context::setRenderingAPI(RenderingAPI::NONE);

	switch (renderingAPI)
	{
	case RenderingAPI::OPENGL:	
		Context::setRenderingAPI(RenderingAPI::OPENGL); 
		return new api::gl::GLWindow(title, width, height);
	
	default:
		return nullptr;
	}
}
