#include <engine/common.hpp>
#include <engine/utils/io.hpp>

#include <engine/graphics/IWindow.hpp>

#include <engine/graphics/opengl/ShaderPipeline.hpp>
#include <engine/graphics/opengl/TextureArray.hpp>
#include <engine/graphics/Camera.hpp>

#include <engine/events/Keys.hpp>

#include <engine/voxels/Block.hpp>
#include <engine/voxels/Chunk.hpp>
#include <engine/voxels/ChunkManager.hpp>

#include <chrono>
#include <thread>

using namespace phx::gfx;
using namespace phx;

int main(int argc, char *argv[])
{
	INITLOGGER("logs/phoenix.log", phx::LogVerbosity::DEBUG);

	gfx::IWindow* window = gfx::IWindow::createWindow(gfx::WindowingAPI::SDL,	// USE GLFW FOR WINDOWING
		"Phoenix!",				// WINDOW TITLE IS PHOENIX
		1280,					// WINDOW WIDTH IS 1280px
		720,					// WINDOW HEIGHT is 720px
		{ 3,3 },				// OPENGL VERSION IS 3.3
		gfx::GLProfile::CORE	// OPENGL PROFILE IS "CORE"
	);

	window->setVSync(true);

	voxels::Block* block = new voxels::Block("core:grass", "Grass", voxels::BlockType::SOLID);
	std::vector<std::string> texForGrass;
	texForGrass.push_back("assets/images/grass_side.png");
	texForGrass.push_back("assets/images/grass_side.png");
	texForGrass.push_back("assets/images/grass_side.png");
	texForGrass.push_back("assets/images/grass_side.png");
	texForGrass.push_back("assets/images/dirt.png");
	texForGrass.push_back("assets/images/grass_top.png");
	block->setTextures(texForGrass);

	voxels::Block* blockAir = new voxels::Block("core:air", "Air", voxels::BlockType::GAS);

	voxels::ChunkManager* world = new voxels::ChunkManager();
	world->setDefaultBlock(block);
	world->testGeneration(10);

	gl::ShaderPipeline* shaderProgram = new gl::ShaderPipeline();
	shaderProgram->addStage(gl::ShaderType::VERTEX_SHADER, File::readFile("assets/shaders/main.vert").c_str());
	shaderProgram->addStage(gl::ShaderType::FRAGMENT_SHADER, File::readFile("assets/shaders/main.frag").c_str());
	shaderProgram->build();

	Matrix4x4 projection = Matrix4x4::perspective(1280.f / 720.f, 45.f, 1000.f, 0.1f);
	Matrix4x4 model;

	FPSCam* cam = new FPSCam(window);

	window->addKeyCallback(static_cast<int>(EventType::PRESSED), static_cast<int>(events::Keys::KEY_ESCAPE), [&cam, &window]() {
		cam->enabled = !cam->enabled;
		if (cam->enabled) {
			window->setCursorState(gfx::CursorState::DISABLED);
		}
		else {
			window->setCursorState(gfx::CursorState::NORMAL);
		}
	});

	window->addKeyCallback(static_cast<int>(EventType::PRESSED), static_cast<int>(events::Keys::KEY_1), [&world]() {
		world->toggleWireframe();
	});

	cam->enabled = true;

	int i = 0;
	int breakTest = 0;

	float last = SDL_GetTicks();

	while (window->isRunning())
	{
		float now = SDL_GetTicks();
		float dt = now - last;
		last = now;
		window->pollEvents();
		cam->update(dt);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		shaderProgram->use();

		shaderProgram->setMat4("u_projection", projection);
		shaderProgram->setMat4("u_view", cam->calculateViewMatrix());
		shaderProgram->setMat4("u_model", model);
		shaderProgram->setUniform1<int>("u_TexArray", 10);

		if (i < 100)
		{
			shaderProgram->setUniform1<int>("TexLayer", 0);
			i++;
		}
		else if (i >= 100 && i < 200)
		{
			shaderProgram->setUniform1<int>("TexLayer", 1);
			i++;
		}
		else
		{
			i = 0;

			world->setBlockAt({ (float)breakTest, 0, 1 }, blockAir);
			breakTest++;
		}

		world->render(10);
		window->swapBuffers();
	}

	DESTROYLOGGER();

	return 0;
}
