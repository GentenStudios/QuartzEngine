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

	RegistryBlock block("core:grass", "Grass", 100);
	
	BlockLibrary::get()->init(block);

	BlockLibrary::get()->registerBlock(block);
}

phx::Application* phx::createApplication()
{
	return new Sandbox();
}