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

#include <engine/graphics/Camera.hpp>

using namespace phx::gfx;
using namespace phx;

int main(int argc, char *argv[])
{
	INITLOGGER("logs/phoenix.log", phx::LogVerbosity::DEBUG);

	gfx::IWindow* window = gfx::IWindow::createWindow(gfx::WindowingAPI::GLFW,	// USE GLFW FOR WINDOWING
														"Phoenix!",				// WINDOW TITLE IS PHOENIX
														1280,					// WINDOW WIDTH IS 1280px
														720,					// WINDOW HEIGHT is 720px
														{ 3,3 },				// OPENGL VERSION IS 3.3
														gfx::GLProfile::CORE	// OPENGL PROFILE IS "CORE"
													);

	window->addKeyCallback(static_cast<int>(EventType::PRESSED) | static_cast<int>(EventType::RELEASED), GLFW_KEY_ESCAPE, [&window]() { window->close(); });

	window->setVSync(false);

	voxels::Block* block = new voxels::Block("core:grass", "Grass", voxels::BlockType::SOLID);
	voxels::Block* blockAir = new voxels::Block("core:air", "Air", voxels::BlockType::GAS);
	voxels::Chunk* chunk = new voxels::Chunk({ 0,0,0 }, 16, block);
	chunk->populateData();
	chunk->buildMesh();

	voxels::ChunkRenderer* chunkRenderer = new voxels::ChunkRenderer();
	chunkRenderer->attachChunk(chunk);
	chunkRenderer->bufferData();

	gl::ShaderPipeline* shaderProgram = new gl::ShaderPipeline();
	shaderProgram->addStage(gl::ShaderType::VERTEX_SHADER, File::readFile("assets/shaders/main.vert").c_str());
	shaderProgram->addStage(gl::ShaderType::FRAGMENT_SHADER, File::readFile("assets/shaders/main.frag").c_str());
	shaderProgram->build();

	gl::TextureArray texture;
	std::vector<std::string> thing;
	thing.push_back("assets/images/dirt.png");
	thing.push_back("assets/images/grass_side.png");
	texture.add(thing);
	texture.bind(10); // Bind to 10th texture unit for no particular reason, except testing the index slot thingy. ya know?

	Matrix4x4 projection = Matrix4x4::perspective(1280.f / 720.f, 45.f, 1000.f, 0.1f);
	Matrix4x4 model;

	FPSCam* cam = new FPSCam(window);

	window->addKeyCallback(static_cast<int>(EventType::RELEASED) | static_cast<int>(EventType::REPEAT) | static_cast<int>(EventType::PRESSED), GLFW_KEY_W, [&cam]() { cam->cameraMoveEvent(CamDir::FORWARD); });
	window->addKeyCallback(static_cast<int>(EventType::RELEASED) | static_cast<int>(EventType::REPEAT) | static_cast<int>(EventType::PRESSED), GLFW_KEY_S, [&cam]() { cam->cameraMoveEvent(CamDir::BACKWARD); });
	window->addKeyCallback(static_cast<int>(EventType::RELEASED) | static_cast<int>(EventType::REPEAT) | static_cast<int>(EventType::PRESSED), GLFW_KEY_A, [&cam]() { cam->cameraMoveEvent(CamDir::LEFT); });
	window->addKeyCallback(static_cast<int>(EventType::RELEASED) | static_cast<int>(EventType::REPEAT) | static_cast<int>(EventType::PRESSED), GLFW_KEY_D, [&cam]() { cam->cameraMoveEvent(CamDir::RIGHT); });
	window->addMouseMoveCallback([&cam](double x, double y) { cam->cameraLookEvent(x, y); });

	cam->enabled = true;

	int i = 0;
	double lastTime = glfwGetTime();
	double lastTimeFPS = glfwGetTime();
	int nbFrames = 0;
	while (window->isRunning())
	{
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		window->pollEvents();
		cam->setDT(deltaTime * 10);
		
		nbFrames++;
		if (currentTime - lastTimeFPS >= 1.0) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%f FPS: \n", double(nbFrames));
			nbFrames = 0;
			lastTimeFPS += 1.0;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		shaderProgram->use();
		texture.bind(10);

		shaderProgram->setMat4("projection", projection);
		shaderProgram->setMat4("view", cam->calculateViewMatrix());
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

		chunkRenderer->render();
		window->swapBuffers();
	}

	DESTROYLOGGER();

	return 0;
}
