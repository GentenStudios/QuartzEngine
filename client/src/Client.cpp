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
	using namespace phx::voxels;

	RegistryBlock block("core:grass", "Grass", 100, BlockType::SOLID);
	
	BlockLibrary::get()->init();

	BlockLibrary::get()->registerBlock(block);

	Chunk* chunk = new Chunk({ 0,0,0 }, 16, "core:grass");
	chunk->populateData();
	chunk->buildMesh();

	while (m_appData->window->isRunning())
	{
		m_appData->window->pollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		int i = 2;
		chunk->render(&i);
		m_appData->window->swapBuffers();
	}
}

phx::Application* phx::createApplication()
{
	return new Sandbox();
}