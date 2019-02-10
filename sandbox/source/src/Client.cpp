#include <client/Client.hpp>
#include <Quartz.hpp>

#include <glad/glad.h>

using namespace client;
using namespace qz;

Sandbox::Sandbox()
{
	m_appRequirements = new ApplicationRequirements();
	m_appRequirements->windowTitle = "Quartz Sandbox";
	m_appRequirements->windowWidth = 1280;
	m_appRequirements->windowHeight = 720;

	m_appRequirements->logFilePath = "Sandbox.log";
	m_appRequirements->logVerbosity = utils::LogVerbosity::DEBUG;
}

void Sandbox::run()
{
	gfx::IWindow* window = m_appData->window;

	window->registerEventListener(std::bind(&Sandbox::onEvent, this, std::placeholders::_1));

	while (window->isRunning())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		window->swapBuffers();
		window->pollEvents();
	}
}

void Sandbox::onEvent(events::Event& event)
{
	events::EventDispatcher dispatcher = events::EventDispatcher(event);

	dispatcher.dispatch<events::KeyPressedEvent>(std::bind(&Sandbox::onKeyEvent, this, std::placeholders::_1));
}

bool Sandbox::onKeyEvent(events::KeyPressedEvent& event)
{
	LDEBUG("Key pressed! wowowowowowow");

	return true;
}
