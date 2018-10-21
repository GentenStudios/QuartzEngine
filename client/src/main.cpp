#include <engine/common.hpp>
#include <engine/graphics/IWindow.hpp>

#include <engine/graphics/opengl/VertexArray.hpp>
#include <engine/graphics/opengl/VertexBuffer.hpp>

#include <GL/glew.h>

#include <SDL.h>

using namespace phx::gfx;
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

	gl::VertexArray* vao = new gl::VertexArray();
	vao->bind();

	gl::VertexBuffer* vbo = new gl::VertexBuffer(gl::VertexBuffer::Target::ARRAY, gl::VertexBuffer::Usage::DYNAMIC_DRAW);
	vbo->bind();
	vbo->setData(static_cast<void*>(vertices), sizeof(vertices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, nullptr);
	glEnableVertexAttribArray(0);

	while (window->isRunning())
	{
		window->pollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		vao->bind();
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window->swapBuffers();
	}

	return 0;
}
