#pragma once

#include "engine/common.hpp"
#include "engine/math/vector2.hpp"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "engine/SDL/context.hpp"

#include "engine/graphics/window.hpp"

namespace phx
{
	namespace sdl
	{

		class SDLWindow : public phx::graphics::Window
		{
		public:
			SDLWindow(const char* title, int width, int height);

			virtual void pollEvents() {}
			virtual void swapBuffers();
			virtual bool isRunning();
			
			virtual void setTitle(const char* title);
			virtual void getSize(int& width, int& height);
			virtual void setFullscreen(bool enabled);
			virtual void setResizable(bool enabled);

			inline SDL_Window* getSDLWindow() const { return m_window; }

		private:
			SDL_Window* m_window;
			SDL_GLContext m_context;

			bool m_running;

		};

	}
}
