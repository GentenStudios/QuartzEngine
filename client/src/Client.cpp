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
	block.setBreakCallback([]() { LDEBUG("Broken a grass block!"); });

	RegistryBlock air("core:air", "Air", 100, BlockType::GAS);
	
	BlockLibrary::get()->init();

	BlockLibrary::get()->registerBlock(block);
	BlockLibrary::get()->registerBlock(air);

	ChunkManager* world = new ChunkManager();
	world->setDefaultBlock("core:grass");
	world->testGeneration(5);

	gl::ShaderPipeline* shaderProgram = new gl::ShaderPipeline();
	shaderProgram->addStage(gl::ShaderType::VERTEX_SHADER, File::readFile("assets/shaders/main.vert").c_str());
	shaderProgram->addStage(gl::ShaderType::FRAGMENT_SHADER, File::readFile("assets/shaders/main.frag").c_str());
	shaderProgram->build();
	
	Matrix4x4 model;

	FPSCam* cam = new FPSCam(m_appData->window);
	cam->enabled = true;

	LDEBUG(world->getBlockAt({ 1, 100, 1 }).getBlockID());
	world->breakBlockAt({0,0,0}, BlockInstance(air.getBlockID()));

	phx::gfx::IWindow* window = m_appData->window;

	window->setResizable(true);

	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_ESCAPE, [&cam, &window]() {
		cam->enabled = !cam->enabled;
		if (cam->enabled)
		{
			window->setCursorState(gfx::CursorState::DISABLED);
		}
		else
		{
			window->setCursorState(gfx::CursorState::NORMAL);
		}
	});

	bool preFocusLostCamEnabled = true;
	window->addWindowEventCallback(events::WindowEventType::FOCUS_LOST, [&cam, &window, &preFocusLostCamEnabled]() {
		preFocusLostCamEnabled = cam->enabled;
		cam->enabled = false;
		window->setCursorState(gfx::CursorState::NORMAL);
	});
	window->addWindowEventCallback(events::WindowEventType::FOCUS_GAINED, [&cam, &window, &preFocusLostCamEnabled]() {
		cam->enabled = preFocusLostCamEnabled;
		if (cam->enabled)
		{
			window->setCursorState(gfx::CursorState::DISABLED);
		}
		else
		{
			window->setCursorState(gfx::CursorState::NORMAL);
		}
	});

	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_F11, [&window]() {
		window->setFullscreen(true);
	});

	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_6, [&window]() {
		window->setFullscreen(false);
	});

	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_1, [&world]() {
		world->toggleWireframe();
	});

	int fps_lasttime = SDL_GetTicks(); //the last recorded time.
	int fps_current; //the current FPS.
	int fps_frames = 0; //frames passed since the last recorded fps.

	float last = SDL_GetTicks();
	while (m_appData->window->isRunning())
	{
		float now = SDL_GetTicks();
		float dt = now - last;
		last = now;

		m_appData->window->pollEvents();
		cam->update(dt);

		// ONLY HERE TEMPORARILY.
		fps_frames++;
		if (fps_lasttime < SDL_GetTicks() - 1000)
		{
			fps_lasttime = SDL_GetTicks();
			fps_current = fps_frames;
			LDEBUG("FPS: ", fps_current);
			fps_frames = 0;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		shaderProgram->use();

		shaderProgram->setMat4("u_projection", cam->getProjection());
		shaderProgram->setMat4("u_view", cam->calculateViewMatrix());
		shaderProgram->setMat4("u_model", model);
		shaderProgram->setUniform1<int>("u_TexArray", 10);

		world->render(10);
		m_appData->window->swapBuffers();
	}
}

phx::Application* phx::createApplication()
{
	return new Sandbox();
}