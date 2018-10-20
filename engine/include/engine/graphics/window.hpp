#pragma once

#include "engine/common.hpp"

namespace phx
{
	namespace graphics
	{

		enum class WindowingAPI
		{
			SDL
		};

		class Window
		{
		public:
			static Window* createWindow(WindowingAPI windowApi, const char* title, int width, int height);

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
