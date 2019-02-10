#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/Application.hpp>

using namespace qz;

extern qz::Application* qz::createApplication();

#ifndef QZ_MAIN_HANDLED
int main(int argc, char** argv)
{
	Application* application = createApplication();

	const ApplicationRequirements* requirements = application->getRequirements();

	INITLOGGER(requirements->logFile, requirements->logVerbosity);

	ApplicationData* appData = new ApplicationData();

	appData->window = gfx::IWindow::createWindow(
		requirements->windowTitle,
		requirements->windowWidth,
		requirements->windowHeight,
		requirements->glVersion,
		requirements->glProfile
	);

	application->setAppData(appData);

	application->run();

	delete application;

	// ENGINE DE-INITIALIZATION
	DESTROYLOGGER();

	return 0;
}
#endif