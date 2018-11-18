#pragma once

#include <engine/core/Core.hpp>
#include <engine/core/Application.hpp>

using namespace phx;

extern phx::Application* phx::createApplication();

#ifndef PHX_MAIN_HANDLED
int main(int argc, char** argv)
{
	phx::Application* application = phx::createApplication();

	application->setup(
		[](phx::ApplicationRequirements* requirements, phx::ApplicationData* data)
		{
			INITLOGGER(requirements->logFile, requirements->logVerbosity);

			data->window = phx::gfx::IWindow::createWindow(
				phx::gfx::WindowingAPI::SDL,
				requirements->windowTitle,
				requirements->windowWidth,
				requirements->windowHeight,
				requirements->glVersion,
				requirements->glProfile
			);
		}
	);

	application->run();

	delete application;

	// ENGINE DE-INITIALISAITON
	DESTROYLOGGER();

	return 0;
}
#endif