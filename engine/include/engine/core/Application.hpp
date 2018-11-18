#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/graphics/IWindow.hpp>

namespace phx
{

	struct ApplicationData
	{
		phx::gfx::IWindow* window;
	};

	class Application
	{
	public:
		Application();
		virtual ~Application() = 0;

		virtual void setup(ApplicationData* data) = 0;

		virtual void run() = 0;
	};

	Application* createApplication();

}