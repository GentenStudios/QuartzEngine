#pragma once

#include "engine/common.hpp"
#include "engine/graphics/Context.hpp"

namespace phx
{
	namespace gfx
	{

		enum class WindowingAPI
		{
			SDL
		};

		class IWindow
		{
		public:
			static IWindow* createWindow(WindowingAPI windowApi, const char* title, int width, int height, GLVersion version, GLProfile profile);

			virtual void pollEvents() = 0;
			virtual void swapBuffers() = 0;
			virtual bool isRunning() = 0;

			virtual void getSize(int& width, int& height) = 0;
			virtual void setTitle(const char* title) = 0;
			virtual void setFullscreen(bool enabled) = 0;
			virtual void setResizable(bool enabled) = 0;
		};

	}
}
