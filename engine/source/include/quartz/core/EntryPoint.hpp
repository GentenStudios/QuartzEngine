#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/Application.hpp>

using namespace qz;

#ifndef QZ_MAIN_HANDLED

extern Application* qz::createApplication();

int main(int argc, char** argv)
{
	Application* application = qz::createApplication();
	const ApplicationRequirements* requirements = application->getAppRequirements();
	ApplicationData* appData = new ApplicationData();

	LOGGER_INIT(requirements->logFilePath, requirements->logVerbosity);

	appData->window = gfx::IWindow::create(requirements->windowTitle, requirements->windowWidth,
										   requirements->windowHeight, 0, gfx::RenderingAPI::OPENGL);

	application->setAppData(appData);

	application->run();

	delete application;
	delete appData;

	LOGGER_DESTROY();

	return 0;
}

#endif