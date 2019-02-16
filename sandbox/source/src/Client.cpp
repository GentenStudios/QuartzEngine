#include <client/Client.hpp>
#include <quartz/core/graphics/Renderer2D.hpp>
#include <quartz/core/utils/Config.hpp>

#include <luamod/luastate.h>
#include <chrono>

using namespace qz;
using namespace gfx;

using namespace client;

Sandbox::Sandbox() :
	m_appRequirements(new ApplicationRequirements()),
	m_appData(new ApplicationData)
{
	m_appRequirements->glProfile = GLProfile::CORE;
	m_appRequirements->glVersion = GLVersionRequired(3, 3);

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
