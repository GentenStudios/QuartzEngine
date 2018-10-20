#include <engine/common.hpp>
#include <engine/graphics/IWindow.hpp>

#include <GL/glew.h>

#include <SDL.h>

using namespace phx;

int main(int argc, char *argv[])
{
	gfx::Window* window = gfx::Window::createWindow(gfx::WindowingAPI::SDL, "Phoenix!", 1280, 720, {3,3}, gfx::GLProfile::CORE);

	glewInit();

	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), static_cast<void*>(vertices), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, nullptr);
	glEnableVertexAttribArray(0);

	while (window->isRunning())
	{
		window->pollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window->swapBuffers();
	}

	return 0;
}
