#include <GL/glew.h>
#include "engine/GLFW/GLFWWindow.hpp"

using namespace phx::glfw;

GLFWWindow::GLFWWindow(const char* title, int width, int height, phx::gfx::GLVersion version, phx::gfx::GLProfile profile, uint8_t aaSamples) :
    m_width(width), m_height(height)
{
    if (!glfwInit())
    {
		ERROR("Ding a dang dong we're the champions! (not really, but don't fight the kings of the world) A team of monkeys will not be dispatched to fix your problems, tell one of the absolute mad pros that GLFW could not start");
        exit(EXIT_FAILURE);
    }

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
		ERROR("Couldn't create window, need OpenGL >= " + std::to_string(version.major) + "." + std::to_string(version.minor));
		exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(m_window);

	if (glewInit() != GLEW_OK)
	{
		ERROR("Holy Molesters. Something seriously went wrong, guess we'll have to fix it now, Tell the pros that GLEW could not initialise. :)");
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, m_width, m_height);

    // on resize
    std::get<GLFWWindow::WindowResizeCallbackBase>(std::get<GLFWWindow::WindowResizeCallbackIndex>(m_callbacks)) = [this] (int w, int h) {
        this->m_width = w;
        this->m_height = h;
    };
    // TODO change
    glfwSetFramebufferSizeCallback(m_window, [] (GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
        auto& base = std::get<GLFWWindow::WindowResizeCallbackBase>(
            std::get<GLFWWindow::WindowResizeCallbackIndex>(
                *static_cast<GLFWWindow::Callbacks_t*>(glfwGetWindowUserPointer(window))));
        auto& user = std::get<GLFWWindow::WindowResizeCallbackUser>(
            std::get<GLFWWindow::WindowResizeCallbackIndex>(
                *static_cast<GLFWWindow::Callbacks_t*>(glfwGetWindowUserPointer(window))));
        base(w, h);
        user(w, h);
    });
    glfwSetWindowUserPointer(m_window, &m_callbacks);
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
    // TODO
	// SDL_SetWindowResizable(m_window, enabled ? SDL_TRUE : SDL_FALSE);
}

void GLFWWindow::setVSync(bool value)
{
    glfwSwapInterval(value ? 1 : 0);
}

void GLFWWindow::updateKeysCallbacks()
{
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mod) {
        auto& callbacks = std::get<GLFWWindow::KeyboardCallbacksIndex>(*static_cast<GLFWWindow::Callbacks_t*>(glfwGetWindowUserPointer(window)));
        for (auto& f: callbacks)
        {
            int ev_idx = std::get<0>(f);

            if (((ev_idx & (int) EventType::RELEASED) != 0 && action == GLFW_RELEASE) ||
                ((ev_idx & (int) EventType::PRESSED) != 0  && action == GLFW_PRESS)   ||
                ((ev_idx & (int) EventType::REPEAT) != 0   && action == GLFW_REPEAT))
                if ((int) std::get<1>(f) == key)
                    std::get<2>(f)();
        }
    });
}

void GLFWWindow::addKeyCallback(int eventType, int key, std::function<void()> callback)
{
    std::get<GLFWWindow::KeyboardCallbacksIndex>(m_callbacks).emplace_back(
        eventType, key, std::move(callback)
    );
    updateKeysCallbacks();
    glfwSetWindowUserPointer(m_window, &m_callbacks);
}

void GLFWWindow::addMouseMoveCallback(std::function<void(double, double)> callback)
{
    std::get<GLFWWindow::MouseMoveCallback>(m_callbacks) = std::move(callback);
    glfwSetCursorPosCallback(m_window, [] (GLFWwindow* window, double x, double y) {
        auto& f = std::get<GLFWWindow::MouseMoveCallback>(*static_cast<GLFWWindow::Callbacks_t*>(glfwGetWindowUserPointer(window)));
        f(x, y);
    });
    glfwSetWindowUserPointer(m_window, &m_callbacks);
}
