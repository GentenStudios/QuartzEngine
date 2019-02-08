#include <quartz/core/graphics/IWindow.hpp>
#include <quartz/core/platform/SDL/SDLWindow.hpp>

using namespace qz::gfx;

IWindow* IWindow::createWindow(const std::string& title, int width, int height, GLVersion version, GLProfile profile)
{
	return new qz::sdl::SDLWindow(title, width, height, version, profile);
}
