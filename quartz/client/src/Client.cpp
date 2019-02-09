#include <client/Client.hpp>
#include <chrono>

#include <quartz/core/graphics/Renderer2D.hpp>

using namespace qz;
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
	m_appRequirements->windowTitle = "Quartz!";

	m_appRequirements->logFile = "QuartzClient.log";
	m_appRequirements->logVerbosity = LogVerbosity::DEBUG;
}

static void QuickSetupLuaBindingsCommon(lm::LuaState& state)
{
	using namespace voxels;

	auto luaLog = [&](int verbosity, const char* msg) {
		Logger::get()->log((LogVerbosity)verbosity, "", 0, "", msg);
	};

	state.SetGlobal("DEBUG", (int)LogVerbosity::DEBUG);
	state.SetGlobal("INFO", (int)LogVerbosity::INFO);
	state.SetGlobal("WARNING", (int)LogVerbosity::WARNING);

	state.SetGlobal("BLOCK_SOLID", (int)BlockType::SOLID);
	state.SetGlobal("BLOCK_GAS", (int)BlockType::GAS);
	state.SetGlobal("BLOCK_LIQUID", (int)BlockType::LIQUID);
	state.SetGlobal("BLOCK_OBJECT", (int)BlockType::OBJECT);
	state.SetGlobal("BLOCK_WATER", (int)BlockType::WATER);

	state.Register("px_log", luaLog);

	auto luaRegisterBlock = [&](std::string blockid, lm::Table blockInfo) {
		std::string displayname = blockInfo.GetProperty<std::string>("displayname", "<unknownblockname>");
		int blockType = blockInfo.GetProperty("type", (int)BlockType::SOLID);
		lm::Array textures = blockInfo.GetProperty<lm::Array>("textures");
		RegistryBlock block(blockid, displayname, 100, (BlockType)blockType);
		block.setBlockTextures(textures.ToVector<std::string>());
	
		BlockLibrary::get()->registerBlock(block);
	};

	state.Register("px_register_block", luaRegisterBlock);

}

void Sandbox::run()
{
	QZ_REGISTER_CONFIG("Controls");

	using namespace voxels;

	lm::LuaState luaState;
	QuickSetupLuaBindingsCommon(luaState);

	luaState.RunFile("assets/scripts/index.lua");

	RegistryBlock air("core:air", "Air", 100, BlockType::GAS);

	BlockLibrary::get()->init();

	BlockLibrary::get()->registerBlock(air);

	// Initialize a world with an air block as the default, a chunk size of 16x16x16, and a random seed dependent on the current time.
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

Application* qz::createApplication()
{
	return new Sandbox();
}
