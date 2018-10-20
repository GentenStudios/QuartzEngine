#include <engine/common.hpp>
#include <engine/SDL/window.hpp>

#include <GL/glew.h>

#include <SDL.h>

using namespace phx;

int main(int argc, char *argv[])
{
	sdl::Window* window = new sdl::Window();

	window->setAttribute(sdl::Feature::DOUBLEBUFFER, true);
	window->setContextInfo(sdl::GLProfile::CORE, sdl::GLVersion {3,3});
	window->initialise("Phoenix!", 1280, 720, sdl::Window::Flags::OPENGL | sdl::Window::Flags::RESIZABLE);

	glewInit();

	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		window->swapBuffers();
	}

	return 0;
}
