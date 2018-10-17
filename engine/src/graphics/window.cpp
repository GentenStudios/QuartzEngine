#include "engine/common.hpp"
#include "engine/graphics/window.hpp"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

using namespace phoenix::graphics;

Window::Window( int width, int height, std::string title )
{
    glfwInit();
    DEBUG("INITIALISED GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow( width, height, title.c_str(), nullptr, nullptr );

    glfwMakeContextCurrent( m_window );

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init();
}

Window::~Window()
{
    glfwDestroyWindow( m_window );
}

int Window::getKeyState(int key)
{
	return glfwGetKey(m_window, key);
}

void Window::setCursorState(CursorState state)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, static_cast<int>(state));
}

XyData Window::getCursorPos() const
{
    double x, y;
    glfwGetCursorPos( m_window, &x, &y );
    return XyData{ static_cast<int>(x), static_cast<int>(y) };
}

void Window::setCursorPos( XyData pos )
{
    glfwSetCursorPos( m_window, pos.x, pos.y );
}

void Window::setCursorPos( int x, int y )
{
    glfwSetCursorPos( m_window, x, y );
}

void Window::defaultHints()
{
    glfwDefaultWindowHints();
}

void Window::hint(int target, int hint)
{
    glfwWindowHint( target, hint );
}

void Window::initialiseSystems()
{
    glfwInit();
}

void Window::swapInterval(int interval)
{
    glfwSwapInterval( interval );
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose( m_window );
}

void Window::setShouldClose( bool close )
{
    glfwSetWindowShouldClose( m_window, close );
}

void Window::swapBuffers()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers( m_window );
}

void Window::pollEvents()
{
    glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

XyData Window::getWindowSize() const
{
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);

	return { w, h };
}
