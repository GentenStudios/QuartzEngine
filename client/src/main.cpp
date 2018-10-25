#include <engine/common.hpp>
#include <engine/utils/io.hpp>

#include <engine/graphics/IWindow.hpp>

#include <engine/graphics/opengl/VertexArray.hpp>
#include <engine/graphics/opengl/VertexBuffer.hpp>
#include <engine/graphics/opengl/VertexAttrib.hpp>
#include <engine/graphics/opengl/ShaderPipeline.hpp>
#include <engine/graphics/opengl/TextureArray.hpp>
#include <engine/SDL/SDLWindow.hpp>
#include <engine/GLFW/GLFWWindow.hpp>

#include <engine/voxels/Block.hpp>
#include <engine/voxels/Chunk.hpp>

using namespace phx::gfx;
using namespace phx;

int main(int argc, char *argv[])
{
	gfx::IWindow* window = gfx::IWindow::createWindow(gfx::WindowingAPI::GLFW,	// USE GLFW FOR WINDOWING
														"Phoenix!",				// WINDOW TITLE IS PHOENIX
														1280,					// WINDOW WIDTH IS 1280px
														720,					// WINDOW HEIGHT is 720px
														{3,3},					// OPENGL VERSION IS 3.3
														gfx::GLProfile::CORE	// OPENGL PROFILE IS "CORE"
	);

	window->setVSync(true);

	window->addKeyCallback((int) glfw::EventType::REPEAT, GLFW_KEY_P, [](){ std::cout << "guess what ? i'm a P !" << std::endl; });

	voxels::Block* block = new voxels::Block("core:grass", "Grass", voxels::BlockType::SOLID);
	voxels::Block* blockAir = new voxels::Block("core:air", "Air", voxels::BlockType::GAS);
	voxels::Chunk* chunk = new voxels::Chunk({0,0,0}, 16, block);
	chunk->populateData();
	
	voxels::ChunkData* chunkData = chunk->getChunkDataPointer();

	gl::VertexArray* vao = new gl::VertexArray();
	vao->bind();

	gl::VertexBuffer* vbo = new gl::VertexBuffer(gl::BufferTarget::ARRAY_BUFFER, gl::BufferUsage::DYNAMIC_DRAW);
	vbo->bind();
	vbo->setData(static_cast<void*>(chunkData->chunkVertices.data()), sizeof(chunkData->chunkVertices[0]) * chunkData->chunkVertices.size());

	gl::VertexAttrib vertAttrib(0, 3, 3, 0, gl::GLType::FLOAT);
	vertAttrib.enable();

	gl::VertexBuffer* uvbo = new gl::VertexBuffer(gl::BufferTarget::ARRAY_BUFFER, gl::BufferUsage::DYNAMIC_DRAW);
	uvbo->bind();
	uvbo->setData(static_cast<void*>(chunkData->chunkUVs.data()), sizeof(chunkData->chunkUVs[0]) * chunkData->chunkUVs.size());

	gl::VertexAttrib uvAttrib(1, 2, 2, 0, gl::GLType::FLOAT);
	uvAttrib.enable();

	gl::ShaderPipeline* shaderProgram = new gl::ShaderPipeline();
	shaderProgram->addStage(gl::ShaderType::VERTEX_SHADER, File::readFile("assets/shaders/main.vert").c_str());
	shaderProgram->addStage(gl::ShaderType::FRAGMENT_SHADER, File::readFile("assets/shaders/main.frag").c_str());
	shaderProgram->build();

	vao->bind();

	gl::TextureArray texture;
	std::vector<std::string> thing;
	thing.push_back("assets/images/dirt.png");
	thing.push_back("assets/images/grass_side.png");
	texture.add(thing);
	texture.bind(10); // Bind to 10th texture unit for no particular reason, except testing the index slot thingy. ya know?

	Matrix4x4 projection = Matrix4x4::perspective(1280.f / 720.f, 45.f, 100.f, 0.1f);
	Matrix4x4 view = Matrix4x4::lookAt({ 50, 40, 12 }, { 5,10,0 }, { 0,1,0 });
	Matrix4x4 model;

	int i = 0;
	while (window->isRunning())
	{
		window->pollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		vao->bind();
		shaderProgram->use();
		texture.bind(10);

		shaderProgram->setMat4("projection", projection);
		shaderProgram->setMat4("view", view);
		shaderProgram->setMat4("model", model);
		shaderProgram->setUniform1<int>("TexArray", 10);

		if (i < 1000)
		{
			shaderProgram->setUniform1<int>("TexLayer", 0);
			i++;
		}
		else if (i >= 1000 && i < 2000)
		{
			shaderProgram->setUniform1<int>("TexLayer", 1);
			i++;
		}
		else
		{
			i = 0;
		}

		vertAttrib.enable();
		uvAttrib.enable();
		glDrawArrays(GL_TRIANGLES, 0, 16*16*16*36);

		window->swapBuffers();
	}

	return 0;
}
