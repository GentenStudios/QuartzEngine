#pragma once

#include <engine/core/Core.hpp>
#include <engine/core/Application.hpp>

using namespace phx;

extern phx::Application* phx::createApplication();

#ifndef PHX_MAIN_HANDLED
int main(int argc, char** argv)
{
	// ENGINE INITIALISAITON


	ApplicationData* appData = new ApplicationData();
	appData->window = phx::gfx::IWindow::createWindow(gfx::WindowingAPI::SDL, "Can't set the fucking title yet.", 1280, 720, { 3, 3 }, phx::gfx::GLProfile::CORE);

	phx::Application* application = phx::createApplication();

	application->setup(appData);
	application->run();

	delete application;

	// ENGINE DE-INITIALISAITON
}
#endif