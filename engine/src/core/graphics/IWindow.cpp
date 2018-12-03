#include <engine/core/graphics/IWindow.hpp>
#include <engine/core/graphics/gl/SDLWindow.hpp>

using namespace phx::gfx;

IWindow* IWindow::createWindow(const std::string& title, int width, int height, GLVersion version, GLProfile profile)
{
	return new phx::sdl::SDLWindow(title, width, height, version, profile);
}
