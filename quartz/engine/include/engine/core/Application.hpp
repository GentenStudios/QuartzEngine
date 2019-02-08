#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/graphics/IWindow.hpp>

namespace phx
{

	struct ApplicationRequirements
	{
		ApplicationRequirements(): 
			glProfile(gfx::GLProfile::CORE), 
			windowWidth(0), windowHeight(0), 
			logVerbosity(LogVerbosity::INFO)
		{}

		phx::gfx::GLProfile glProfile;
		phx::gfx::GLVersion glVersion;

		int windowWidth;
		int windowHeight;
		std::string windowTitle;

		std::string logFile;
		phx::LogVerbosity logVerbosity;
	};

	struct ApplicationData
	{
		phx::gfx::IWindow* window;
	};

	class Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		virtual const ApplicationRequirements* getRequirements() = 0;
		virtual void setAppData(ApplicationData* appData) = 0;

		virtual void run() = 0;
	};

	Application* createApplication();

}