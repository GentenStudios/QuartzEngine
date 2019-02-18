#include <client/Client.hpp>
#include <quartz/core/utilities/Config.hpp>

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <chrono>

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
		window->pollEvents();
		
		window->startGUIFrame();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, 1.0f);
	
		ImGui::ShowDemoWindow();

		window->endGUIFrame();
		window->swapBuffers();
	}
}

bool onClose(events::WindowCloseEvent e)
{
	LDEBUG("WOW! WINDOW IS CLOSING DOWN.");
	return true;
}

bool Sandbox::onKeyPress(events::KeyPressedEvent& e)
{
	if (e.getKeyCode() == events::Key::KEY_W)
	{
		m_clearColor = { 0, 1, 0 };
	}
	else if (e.getKeyCode() == events::Key::KEY_A)
	{
		m_clearColor = { 1, 0, 0 };
	}
	else if (e.getKeyCode() == events::Key::KEY_S)
	{
		m_clearColor = { 0, 0, 1 };
	}
	else if (e.getKeyCode() == events::Key::KEY_D)
	{
		m_clearColor = { 1, 1, 1 };
	}
	else
	{
		m_clearColor = { 0, 0, 0 };
	}

	return true;
}

bool Sandbox::onClose(events::WindowCloseEvent& e)
{
	LDEBUG("Sandbox is shutting down.");

	return true;
}

void Sandbox::onEvent(events::Event& e)
{
	auto test = events::EventDispatcher(e);
	test.dispatch<events::WindowCloseEvent>(std::bind(&Sandbox::onClose, this, std::placeholders::_1));
	test.dispatch<events::KeyPressedEvent>(std::bind(&Sandbox::onKeyPress, this, std::placeholders::_1));
}

bool onClose2(events::WindowCloseEvent e)
{
	LDEBUG("WOW! THE SECOND EVENT HANDLER IS WORKING!");
	return true;
}
