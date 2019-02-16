#include <client/Client.hpp>
#include <quartz/core/utils/Config.hpp>

#include <chrono>

using namespace qz;
using namespace gfx;

using namespace client;

Sandbox::Sandbox() :
	m_appRequirements(new ApplicationRequirements()),
	m_appData(new ApplicationData)
{
	m_appRequirements->windowWidth = 1280;
	m_appRequirements->windowHeight = 720;
	m_appRequirements->windowTitle = "Quartz!";

	m_appRequirements->logFile = "QuartzClient.log";
	m_appRequirements->logVerbosity = LogVerbosity::DEBUG;
}

void Sandbox::run()
{
	LDEBUG("DEBUG MESSAGE");
}

Application* qz::createApplication()
{
	return new Sandbox();
}
