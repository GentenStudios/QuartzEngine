#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/graphics/IWindow.hpp>
#include <quartz/core/utilities/Logger.hpp>

namespace qz
{
	struct ApplicationRequirements
	{
		std::string windowTitle;
		int windowWidth = 1280;
		int windowHeight = 720;

		std::string logFilePath;
		utils::LogVerbosity logVerbosity = utils::LogVerbosity::INFO;
	};

	struct ApplicationData
	{
		gfx::IWindow* window;

		ApplicationData() : window(nullptr) {}
		~ApplicationData() {}
	};

	class QZ_API Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		virtual const ApplicationRequirements* getAppRequirements() = 0;
		virtual void setAppData(ApplicationData* appData) = 0;

		virtual void run() = 0;
	};

	Application* createApplication();
}
