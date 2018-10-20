#pragma once

#include "engine/common.hpp"
#include "engine/math/vector2.hpp"

#include <SDL.h>
#include "engine/SDL/context.hpp"

namespace phx
{
	namespace sdl
	{

		class Window
		{
		public:

			enum class Flags : uint32_t {
				FULLSCREEN         = SDL_WINDOW_FULLSCREEN,
				OPENGL             = SDL_WINDOW_OPENGL,
				RESIZABLE          = SDL_WINDOW_RESIZABLE,
				HIGHDPI           = SDL_WINDOW_ALLOW_HIGHDPI
			};

			Window();
			~Window();

			inline SDL_Window* getWindow() const { return m_window; }

			void setAttribute(Attribute attribute, int value) const;
			void setAttribute(Feature feature, bool value) const;
			void setContextInfo(GLProfile profile, GLVersion version) const;

			void initialise(const char* title, int width, int height, uint32_t flags = 0);

			void setTitle(const char* title) const;
			void resize();

			phx::Vector2 getSize() const;
			int getWidth() const;
			int getHeight() const;

		private:
			SDL_Window* m_window;

		};

	}
}
