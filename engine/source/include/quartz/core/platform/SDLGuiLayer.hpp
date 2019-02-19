#pragma once

#include <SDL.h>

namespace qz
{
	namespace gfx
	{
		class SDLGuiLayer 
		{
		public:
			void init(SDL_Window* window, SDL_GLContext* context);

			void startFrame();
			void endFrame();

			void pollEvents(SDL_Event* event);

		private:
			SDL_Window* m_window;
			SDL_GLContext* m_context;
		};
	}
}
