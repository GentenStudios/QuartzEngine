#include "engine/graphics/IWindow.hpp"

#include "engine/SDL/SDLWindow.hpp"

using namespace phx::graphics;

Window* Window::createWindow(WindowingAPI windowingAPI, const char* title, int width, int height, GLVersion version, GLProfile profile)
{
	switch (windowingAPI)
	{
	case WindowingAPI::SDL:
		return new phx::sdl::SDLWindow(title, width, height, version, profile);
	}

	return nullptr;
}