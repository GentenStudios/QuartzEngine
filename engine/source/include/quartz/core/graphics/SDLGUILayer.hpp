#pragma once

#include <SDL.h>

namespace qz
{
	namespace gfx
	{
		class SDLGUILayer
		{
		public:
			void init(SDL_Window* window, SDL_GLContext* ctx);
			
			void startFrame();
			void endFrame();

			void pollEvents(SDL_Event* e);
		private:
			SDL_Window* m_window;
			SDL_GLContext* m_context;
		};
	}
}
