#include "engine/SDL/SDLWindow.hpp"

using namespace phx::sdl;

SDLWindow::SDLWindow(const char* title, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);

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
