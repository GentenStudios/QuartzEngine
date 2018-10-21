#include <engine/common.hpp>
#include <engine/graphics/IWindow.hpp>

#include <engine/graphics/opengl/VertexArray.hpp>
#include <engine/graphics/opengl/VertexBuffer.hpp>
#include <engine/graphics/opengl/VertexAttrib.hpp>
#include <engine/graphics/opengl/ShaderPipeline.hpp>

#include <GL/glew.h>

#include <SDL.h>

using namespace phx::gfx;
using namespace phx;

const char *vertexShaderSource = "#version 330 \n layout (location = 0) in vec3 pos; void main() { gl_Position = vec4(pos.x, pos.y, pos.z, 1.0); }";
const char *fragmentShaderSource = "#version 330 \n out vec4 FragColor; void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }";

int main(int argc, char *argv[])
{
	gfx::IWindow* window = gfx::IWindow::createWindow(gfx::WindowingAPI::SDL, "Phoenix!", 1280, 720, {3,3}, gfx::GLProfile::CORE);

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

	gl::VertexAttrib vertAttrib(0, 3, 3, 0);
	vertAttrib.enable();

	gl::ShaderPipeline* shaderProgram = new gl::ShaderPipeline();
	shaderProgram->addStage(gl::ShaderStage::VERTEX_SHADER, vertexShaderSource);
	shaderProgram->addStage(gl::ShaderStage::FRAGMENT_SHADER, fragmentShaderSource);
	shaderProgram->build();

	while (window->isRunning())
	{
		window->pollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		vao->bind();
		shaderProgram->use();
		vertAttrib.enable();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window->swapBuffers();
	}

	return 0;
}
