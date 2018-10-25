#include "engine/SDL/SDLWindow.hpp"
#include <GL/glew.h>

using namespace phx::sdl;

SDLWindow::SDLWindow(const char* title, int width, int height, phx::gfx::GLVersion version, phx::gfx::GLProfile profile)
{
	if(!SDL_Init(SDL_INIT_EVERYTHING))
	{
		ERROR("Uh oh! We had a booboo. Just tell the pros this: SDL couldn't initialise itself");
		exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version.major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version.minor);

	uint32_t SDLProfile = SDL_GL_CONTEXT_PROFILE_CORE;
	switch (profile)
	{
	case phx::gfx::GLProfile::CORE:
		SDLProfile = SDL_GL_CONTEXT_PROFILE_CORE;
		break;
	case phx::gfx::GLProfile::COMPATABILITY:
		SDLProfile = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
		break;
	case phx::gfx::GLProfile::ES:
		SDLProfile = SDL_GL_CONTEXT_PROFILE_ES;
		break;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDLProfile);

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (m_window != nullptr)
	{
		SDL_Quit();
		ERROR("Couldn't create window, need OpenGL >= " + std::to_string(version.major) + "." + std::to_string(version.minor));
		exit(EXIT_FAILURE);
	}

	m_context = SDL_GL_CreateContext(m_window);

	if (glewInit() != GLEW_OK)
	{
		ERROR("Uh Oh! There was a booboo, and we can't fix it :(. Tell the pros that an OpenGL context could not be created. Sorry for the inconvenience!");
		exit(EXIT_FAILURE);
	}

	SDL_ShowWindow(m_window);

	m_running = true;
}

void SDLWindow::pollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) > 0)
	{
		if (event.type == SDL_QUIT)
			m_running = false;
	}
}

void SDLWindow::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

bool SDLWindow::isRunning()
{
	return m_running;
}

void SDLWindow::setTitle(const char* title)
{
	SDL_SetWindowTitle(m_window, title);
}

void SDLWindow::getSize(int& width, int& height)
{
	SDL_GetWindowSize(m_window, &width, &height);
}

void phx::sdl::SDLWindow::setFullscreen(bool enabled)
{
	SDL_SetWindowFullscreen(m_window, enabled ? SDL_WINDOW_FULLSCREEN : 0);
}

void phx::sdl::SDLWindow::setResizable(bool enabled)
{
	SDL_SetWindowResizable(m_window, enabled ? SDL_TRUE : SDL_FALSE);
}
