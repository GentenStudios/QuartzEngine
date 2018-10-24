#include "engine/GLFWWindow/GLFWWindowWindow.hpp"
#include <GL/glew.h>

using namespace phx::glfw;

GLFWWindow::GLFWWindow(const char* title, int width, int height, phx::gfx::GLVersion version, phx::gfx::GLProfile profile, uint8_t aaSamples) :
    m_width(width), m_height(height)
{
    if (!glfwInit())
        throw std::runtime_error("Couldn't create window");
	
    glfwWindowHint(GLFW_SAMPLES, aaSamples);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version.minor);

	uint32_t GLFWProfile = GLFW_OPENGL_CORE_PROFILE;
	switch (profile)
	{
	case phx::gfx::GLProfile::CORE:
		GLFWProfile = GLFW_OPENGL_CORE_PROFILE;
		break;
	case phx::gfx::GLProfile::COMPATABILITY:
		GLFWProfile = GLFW_OPENGL_COMPAT_PROFILE;
		break;
    // TODO
	/*case phx::gfx::GLProfile::ES:
		GLFWProfile = SDL_GL_CONTEXT_PROFILE_ES;
		break;*/
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFWProfile);

#ifdef PHX_APPLE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
    if (m_window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Couldn't create window, need OpenGL >= " + std::to_string(version.major) + "." + std::to_string(version.minor));
    }
    glfwMakeContextCurrent(m_window);

	if (glewInit() != GLEW_OK)
	{
		ERROR("OPENGL CONTEXT COULD NOT BE MADE PROPERLY");
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, m_width, m_height);

	m_running = true;
}

GLFWWindow::~GLFWWindow()
{
    glfwTerminate();
    m_window = nullptr;
}

void GLFWWindow::pollEvents()
{
	glfwPollEvents();
}

void GLFWWindow::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool GLFWWindow::isRunning()
{
	return !glfwWindowShouldClose(m_window);
}

void GLFWWindow::setTitle(const char* title)
{
	glfwSetWindowTitle(m_window, title);
}

void GLFWWindow::getSize(int& width, int& height)
{
	glfwGetWindowSize(m_window, &width, &height);
}

void GLFWWindow::setFullscreen(bool enabled)
{
    // TODO
	// SDL_SetWindowFullscreen(m_window, enabled ? SDL_WINDOW_FULLSCREEN : 0);
}

void GLFWWindow::setResizable(bool enabled)
{
	SDL_SetWindowResizable(m_window, enabled ? SDL_TRUE : SDL_FALSE);
}

void GLFWWindow::setVSync(bool value)
{
    glfwSwapInterval(value ? 1 : 0);
}