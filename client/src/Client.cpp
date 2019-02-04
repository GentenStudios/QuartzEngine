#include <client/Client.hpp>
#include <chrono>

#include <engine/core/graphics/Renderer2D.hpp>

using namespace phx;
using namespace gfx;

using namespace client;

#include <luamod/luastate.h>

Sandbox::Sandbox() :
	m_appRequirements(new ApplicationRequirements()),
	m_appData(new ApplicationData)
{
	m_appRequirements->glProfile = GLProfile::CORE;
	m_appRequirements->glVersion = GLVersion(3, 3);

	m_appRequirements->windowWidth = 1280;
	m_appRequirements->windowHeight = 720;
	m_appRequirements->windowTitle = "Phoenix!";

	m_appRequirements->logFile = "PhoenixClient.log";
	m_appRequirements->logVerbosity = LogVerbosity::DEBUG;
}

static void QuickSetupLuaBindingsCommon(lm::LuaState& state)
{
	auto luaLog = [&](int verbosity, const char* msg) {
		Logger::get()->log((LogVerbosity)verbosity, "", 0, "", msg);
	};

	state.SetGlobal("DEBUG", (int)LogVerbosity::DEBUG);
	state.SetGlobal("INFO", (int)LogVerbosity::INFO);
	state.SetGlobal("WARNING", (int)LogVerbosity::WARNING);

	state.Register("px_log", luaLog);
}

void Sandbox::run()
{
	PHX_REGISTER_CONFIG("Controls");

	using namespace voxels;

	lm::LuaState luaState;
	QuickSetupLuaBindingsCommon(luaState);

	luaState.RunFile("assets/scripts/index.lua");

	RegistryBlock block("core:grass", "Grass", 100, BlockType::SOLID);
	std::vector<std::string> texForGrass;
	texForGrass.emplace_back("assets/textures/grass_side.png");
	texForGrass.emplace_back("assets/textures/grass_side.png");
	texForGrass.emplace_back("assets/textures/grass_side.png");
	texForGrass.emplace_back("assets/textures/grass_side.png");
	texForGrass.emplace_back("assets/textures/dirt.png");
	texForGrass.emplace_back("assets/textures/grass_top.png");
	block.setBlockTextures(texForGrass);
	block.setBreakCallback([]() { LDEBUG("Broken a grass block!"); });

	RegistryBlock blockDirt("core:dirt", "dirt", 100, BlockType::SOLID);
	std::vector<std::string> texForDirt;
	texForDirt.emplace_back("assets/textures/dirt.png");
	texForDirt.emplace_back("assets/textures/dirt.png");
	texForDirt.emplace_back("assets/textures/dirt.png");
	texForDirt.emplace_back("assets/textures/dirt.png");
	texForDirt.emplace_back("assets/textures/dirt.png");
	texForDirt.emplace_back("assets/textures/dirt.png");
	blockDirt.setBlockTextures(texForDirt);
	blockDirt.setBreakCallback([]() { LDEBUG("Broken a dirt block!"); });

	RegistryBlock air("core:air", "Air", 100, BlockType::GAS);

	BlockLibrary::get()->init();

	BlockLibrary::get()->registerBlock(block);
	BlockLibrary::get()->registerBlock(blockDirt);
	BlockLibrary::get()->registerBlock(air);

	// Initialise a world with an air block as the default, a chunk size of 16x16x16, and a random seed dependent on the current time.
	ChunkManager* world = new ChunkManager("core:air", 16, static_cast<unsigned int>(time(nullptr)));

	m_player = std::make_unique<Player>(m_appData->window, world);

	gl::ShaderPipeline* shaderProgram = new gl::ShaderPipeline();
	shaderProgram->addStage(gl::ShaderType::VERTEX_SHADER, File::readFile("assets/shaders/main.vert").c_str());
	shaderProgram->addStage(gl::ShaderType::FRAGMENT_SHADER, File::readFile("assets/shaders/main.frag").c_str());
	shaderProgram->build();

	Matrix4x4 model;

	IWindow* window = m_appData->window;
	int ww, wh;
	window->getSize(ww, wh);

	bool fullscreen = false;
	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_F11, [&window, &fullscreen]()
	{
		fullscreen = !fullscreen;
		window->setFullscreen(fullscreen);
	});

	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_RETURN, [&window, &fullscreen]()
	{
		LDEBUG("ENTER!");
		window->pollEvents();
		if (window->isKeyDown(events::Keys::KEY_LALT))
		{
			fullscreen = !fullscreen;
			window->setFullscreen(fullscreen);
		}
	});

	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_1, [&world]()
	{
		world->toggleWireframe();
	});

	Renderer2D renderer(
		Matrix4x4::ortho(0.f, static_cast<float>(ww), 0.f, static_cast<float>(wh), 1.f, -1.f),
		"assets/shaders/ui.vert",
		"assets/shaders/ui.frag"
	);

	std::size_t fpsLastTime = SDL_GetTicks();
	int fpsCurrent; // the current FPS.
	int fpsFrames = 0; // frames passed since the last recorded fps.

	world->determineGeneration(m_player->getPosition());

	float last = static_cast<float>(SDL_GetTicks());
	while (m_appData->window->isRunning())
	{
		m_appData->window->pollEvents();
		float now = static_cast<float>(SDL_GetTicks());
		float dt = now - last;
		last = now;

		m_player->tick(dt);

		// ONLY HERE TEMPORARILY.
		fpsFrames++;
		if (fpsLastTime < SDL_GetTicks() - 1000)
		{
			fpsLastTime = SDL_GetTicks();
			fpsCurrent = fpsFrames;
			LDEBUG("FPS: ", fpsCurrent);
			fpsFrames = 0;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		shaderProgram->use();

		m_player->applyTo(shaderProgram);
		shaderProgram->setMat4("u_model", model);
		shaderProgram->setUniform1<int>("u_TexArray", 10);

		world->render(10);

		renderer.begin();
		renderer.fillCircle({ww / 2.f, wh / 2.f}, 3, 7, {1.f, 1.f, 1.f});
		renderer.end();
		renderer.draw();

		m_appData->window->swapBuffers();
	}
}

Application* phx::createApplication()
{
	return new Sandbox();
}
