#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/utils/Logging.hpp>

#include <quartz/core/graphics/IWindow.hpp>

namespace qz
{
	struct ApplicationRequirements
	{
		ApplicationRequirements(): 
			glProfile(gfx::GLProfile::CORE), 
			windowWidth(0), windowHeight(0), 
			logVerbosity(LogVerbosity::INFO)
		{}

		gfx::GLProfile glProfile;
		gfx::GLVersionRequired glVersion;

		int windowWidth;
		int windowHeight;
		std::string windowTitle;

		std::string logFile;
		LogVerbosity logVerbosity;
	};

	struct ApplicationData
	{
		gfx::IWindow* window;
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