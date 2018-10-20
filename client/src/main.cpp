#include <engine/common.hpp>
#include <engine/graphics/IWindow.hpp>

#include <GL/glew.h>

#include <SDL.h>

using namespace phx;

int main(int argc, char *argv[])
{
	graphics::Window* window = graphics::Window::createWindow(graphics::WindowingAPI::SDL, "Phoenix!", 1280, 720);

	glewInit();

	while (window->isRunning())
	{
		window->pollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		window->swapBuffers();
	}

	return 0;
}
