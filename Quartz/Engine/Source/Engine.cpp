#include <Quartz/Engine.hpp>

using namespace qz;

Engine::Engine()  = default;
Engine::~Engine() = default;

Engine* Engine::instance()
{
	static Engine engine;
	return &engine;
}

void Engine::init(EngineFlags flags, EngineInitData initData)
{
	m_appName = std::move(initData.appName);
	m_dataDir = std::move(initData.dataDir);

	if (ENUMhasFlag(flags, EngineFlags::INIT_GRAPHICS))
	{
		// init graphics
		m_graphicsInit = true;
	}

	if (ENUMhasFlag(flags, EngineFlags::INIT_THREADING))
	{
		// init threading
		m_threadingAllowed = true;
	}

	if (ENUMhasFlag(flags, EngineFlags::INIT_LOGGING))
	{
		// init logger.
	}
}

void Engine::destroy()
{
	if (m_graphicsInit)
	{
		// kill graphics resources.
	}

	// check if logger is alive & kill.
}
