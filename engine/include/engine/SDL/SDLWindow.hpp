#pragma once

#include "engine/common.hpp"
#include "engine/math/Vector2.hpp"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "engine/graphics/Context.hpp"

#include "engine/graphics/IWindow.hpp"

#include <vector>

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
			virtual void close();
			
			virtual void setTitle(const char* title);
			virtual void getSize(int& width, int& height);
			virtual void setFullscreen(bool enabled);
			virtual void setResizable(bool enabled);
			virtual void setCursorState(phx::gfx::CursorState cursorState);

			virtual void setVSync(bool value);
			virtual void addKeyCallback(int eventType, int key, std::function<void()> callback);
			virtual void addMouseMoveCallback(std::function<void(double, double)> callback);

			inline SDL_Window* getSDLWindow() const { return m_window; }

			virtual bool isKeyDown(int key);
			virtual TVector2<int> getMousePosition();

			virtual void setMousePosition(TVector2<int> newPos);

		private:
			SDL_Window* m_window;
			SDL_GLContext m_context;

			bool m_running;
			
			struct KeyEvent_t {
				int eventType;
				int key;
				std::function<void()> callback;
			};

			struct MouseMoveEvent_t {
				std::function<void(double,double)> callback;
			};

			std::vector<KeyEvent_t> m_keyEvents;
			std::vector<MouseMoveEvent_t> m_mouseMoveEvents;
		};

	}
}
