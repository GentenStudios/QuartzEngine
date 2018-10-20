#include "engine/graphics/IWindow.hpp"

#include "engine/SDL/SDLWindow.hpp"

using namespace phx::graphics;

Window* Window::createWindow(WindowingAPI windowingAPI, const char* title, int width, int height)
{
	switch (windowingAPI)
	{
	case WindowingAPI::SDL:
		return new phx::sdl::SDLWindow(title, width, height);
	}

	return nullptr;
}