#pragma once

#include "engine/common.hpp"
#include "engine/math/Vector2.hpp"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "engine/graphics/Context.hpp"

#include "engine/graphics/IWindow.hpp"

namespace phx
{
	namespace sdl
	{

		class SDLWindow : public phx::gfx::IWindow
		{
		public:
			SDLWindow(const char* title, int width, int height, phx::gfx::GLVersion version, phx::gfx::GLProfile profile);

			virtual void pollEvents();
			virtual void swapBuffers();
			virtual bool isRunning();
			
			virtual void setTitle(const char* title);
			virtual void getSize(int& width, int& height);
			virtual void setFullscreen(bool enabled);
			virtual void setResizable(bool enabled);

			virtual void setVSync(bool value);
			virtual void addKeyCallback(int eventType, int key, std::function<void()> callback) {}
			virtual void addMouseMoveCallback(std::function<void(double, double)> callback) {}

			inline SDL_Window* getSDLWindow() const { return m_window; }

		private:
			SDL_Window* m_window;
			SDL_GLContext m_context;

			bool m_running;

		};

	}
}
