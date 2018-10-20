#include "engine/SDL/window.hpp"

using namespace phx::sdl;

Window::Window()
{}

Window::~Window()
{
	SDL_GL_DeleteContext(m_window);
	SDL_DestroyWindow(m_window);
}

void Window::setAttribute(Attribute attribute, int value) const
{
	SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attribute), value);
}

void Window::setAttribute(Feature feature, bool enabled) const
{
	SDL_GL_SetAttribute(static_cast<SDL_GLattr>(feature), enabled ? 0 : 1);
}

void Window::initialise(const char* title, int width, int height, uint32_t flags)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
}

void Window::setContextInfo(GLProfile profile, GLVersion version) const
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version.major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version.minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, static_cast<SDL_GLattr>(profile));
}

void Window::setTitle(const char* title) const
{
	SDL_SetWindowTitle(m_window, title);
}

phx::Vector2 Window::getSize() const
{
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	return {w, h};
}

int Window::getWidth() const
{
	return static_cast<int>(getSize().x);
}

int Window::getHeight() const
{
	return static_cast<int>(getSize().y);
}
