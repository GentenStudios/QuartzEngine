#include <client/Client.hpp>

#include <chrono>
#include <thread>

using namespace phx::gfx;
using namespace phx;


using namespace client;

Sandbox::Sandbox() :
	m_appRequirements(new phx::ApplicationRequirements()),
	m_appData(new phx::ApplicationData)
{
	using namespace phx::gfx;
	using namespace phx;

	m_appRequirements->glProfile = GLProfile::CORE;
	m_appRequirements->glVersion = GLVersion(3, 3);

	m_appRequirements->windowWidth = 1280;
	m_appRequirements->windowHeight = 720;
	m_appRequirements->windowTitle = "Phoenix!";

	m_appRequirements->logFile = "PhoenixClient.log";
	m_appRequirements->logVerbosity = LogVerbosity::DEBUG;
}

Sandbox::~Sandbox()
{}

void Sandbox::run()
{
	PHX_REGISTER_CONFIG("Controls");

	using namespace phx::voxels;

	RegistryBlock block("core:grass", "Grass", 100, BlockType::SOLID);
	std::vector<std::string> texForGrass;
	texForGrass.push_back("assets/images/grass_side.png");
	texForGrass.push_back("assets/images/grass_side.png");
	texForGrass.push_back("assets/images/grass_side.png");
	texForGrass.push_back("assets/images/grass_side.png");
	texForGrass.push_back("assets/images/dirt.png");
	texForGrass.push_back("assets/images/grass_top.png");
	block.setBlockTextures(texForGrass);
	
	BlockLibrary::get()->init();

	BlockLibrary::get()->registerBlock(block);

	Chunk* chunk = new Chunk({ 0,0,0 }, 16, "core:grass");
	chunk->populateData();
	chunk->buildMesh();

	gl::ShaderPipeline* shaderProgram = new gl::ShaderPipeline();
	shaderProgram->addStage(gl::ShaderType::VERTEX_SHADER, File::readFile("assets/shaders/main.vert").c_str());
	shaderProgram->addStage(gl::ShaderType::FRAGMENT_SHADER, File::readFile("assets/shaders/main.frag").c_str());
	shaderProgram->build();
	
	Matrix4x4 projection = Matrix4x4::perspective(1280.f / 720.f, 45.f, 1000.f, 0.1f);
	Matrix4x4 model;

	FPSCam* cam = new FPSCam(m_appData->window);
	cam->enabled = true;

	float last = SDL_GetTicks();
	while (m_appData->window->isRunning())
	{
		float now = SDL_GetTicks();
		float dt = now - last;
		last = now;

		m_appData->window->pollEvents();
		cam->update(dt);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		shaderProgram->use();

		shaderProgram->setMat4("u_projection", projection);
		shaderProgram->setMat4("u_view", cam->calculateViewMatrix());
		shaderProgram->setMat4("u_model", model);
		shaderProgram->setUniform1<int>("u_TexArray", 10);

		int i = 2;
		chunk->render(&i);
		m_appData->window->swapBuffers();
	}
}

phx::Application* phx::createApplication()
{
	return new Sandbox();
}