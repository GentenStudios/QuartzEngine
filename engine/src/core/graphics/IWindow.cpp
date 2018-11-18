#include <engine/core/graphics/IWindow.hpp>
#include <engine/core/graphics/gl/SDLWindow.hpp>

using namespace phx::gfx;

IWindow* IWindow::createWindow(WindowingAPI windowingAPI, std::string& title, int width, int height, GLVersion version, GLProfile profile)
{
	switch (windowingAPI)
	{
	case WindowingAPI::SDL:
		return new phx::sdl::SDLWindow(title, width, height, version, profile);
	}

	return nullptr;
}
