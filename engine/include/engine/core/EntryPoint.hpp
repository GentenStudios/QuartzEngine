#pragma once

#include <engine/core/Core.hpp>
#include <engine/core/Application.hpp>

using namespace phx;

extern phx::Application* phx::createApplication();

#ifndef PHX_MAIN_HANDLED
int main(int argc, char** argv)
{
	phx::Application* application = phx::createApplication();

	const phx::ApplicationRequirements* requirements = application->getRequirements();

	INITLOGGER(requirements->logFile, requirements->logVerbosity);

	phx::ApplicationData* appData = new ApplicationData();

	appData->window = phx::gfx::IWindow::createWindow(
		requirements->windowTitle,
		requirements->windowWidth,
		requirements->windowHeight,
		requirements->glVersion,
		requirements->glProfile
	);

	application->setAppData(appData);

	application->run();

	delete application;

	// ENGINE DE-INITIALISAITON
	DESTROYLOGGER();

	return 0;
}
#endif