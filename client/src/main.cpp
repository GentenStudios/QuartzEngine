#include <engine/common.hpp>
#include <engine/graphics/IWindow.hpp>

#include <engine/graphics/opengl/VertexArray.hpp>
#include <engine/graphics/opengl/VertexBuffer.hpp>
#include <engine/graphics/opengl/VertexAttrib.hpp>
#include <engine/graphics/opengl/ShaderPipeline.hpp>

#include <engine/voxels/Block.hpp>
#include <engine/voxels/Chunk.hpp>

using namespace phx::gfx;
using namespace phx;

const char* vertexShaderSource =	"#version 330 core \n"
									"layout (location = 0) in vec3 aPos; \n"
									"uniform mat4 model; \n"
									"uniform mat4 view; \n"
									"uniform mat4 projection; \n"
									"void main() \n"
									"{ \n"
									"gl_Position = projection * view * model * vec4(aPos, 1.0); \n"
									"}";

const char* fragmentShaderSource = "#version 330 \n out vec4 FragColor; void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }";

int main(int argc, char *argv[])
{
	gfx::IWindow* window = gfx::IWindow::createWindow(gfx::WindowingAPI::SDL,	// USE SDL FOR WINDOWING 
														"Phoenix!",				// WINDOW TITLE IS PHOENIX
														1280,					// WINDOW WIDTH IS 1280px
														720,					// WINDOW HEIGHT is 720px
														{3,3},					// OPENGL VERSION IS 3.3
														gfx::GLProfile::CORE	// OPENGL PROFILE IS "CORE"
	);

	voxels::Block* block = new voxels::Block("core:grass", "Grass", voxels::BlockType::SOLID);
	voxels::Chunk* chunk = new voxels::Chunk({0,0,0}, 16, block);
	chunk->populateData();
	
	voxels::ChunkData* chunkData = chunk->getChunkDataPointer();

	gl::VertexArray* vao = new gl::VertexArray();
	vao->bind();

	gl::VertexBuffer* vbo = new gl::VertexBuffer(gl::VertexBuffer::Target::ARRAY, gl::VertexBuffer::Usage::DYNAMIC_DRAW);
	vbo->bind();
	vbo->setData(static_cast<void*>(chunkData->chunkVertices.data()), sizeof(chunkData->chunkVertices[0]) * chunkData->chunkVertices.size());

	gl::VertexAttrib vertAttrib(0, 3, 3, 0);
	vertAttrib.enable();

	gl::ShaderPipeline* shaderProgram = new gl::ShaderPipeline();
	shaderProgram->addStage(gl::ShaderStage::VERTEX_SHADER, vertexShaderSource);
	shaderProgram->addStage(gl::ShaderStage::FRAGMENT_SHADER, fragmentShaderSource);
	shaderProgram->build();

	Matrix4x4 projection = Matrix4x4::perspective(1280.f / 720.f, 45.f, 100.f, 0.1f);
	Matrix4x4 view = Matrix4x4::lookAt({ -50, 5, 5 }, { 0,10,0 }, { 0,1,0 });
	Matrix4x4 model;

	while (window->isRunning())
	{
		window->pollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		vao->bind();
		shaderProgram->use();

		shaderProgram->setMat4("projection", projection);
		shaderProgram->setMat4("view", view);
		shaderProgram->setMat4("model", model);

		vertAttrib.enable();
		glDrawArrays(GL_TRIANGLES, 0, 16*16*16*36);

		window->swapBuffers();
	}

	return 0;
}
