#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/graphics/IWindow.hpp>

namespace phx
{

	struct ApplicationRequirements
	{
		ApplicationRequirements() {}

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

		using SetupCallback = std::function<void(ApplicationRequirements*, ApplicationData*)>;

		Application() {};
		virtual ~Application() {};

		virtual void setup(SetupCallback setupCallback) = 0;

		virtual void run() = 0;
	};

	Application* createApplication();

}