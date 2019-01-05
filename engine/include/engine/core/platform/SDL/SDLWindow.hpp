#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <engine/core/math/Vector2.hpp>

#include <engine/core/graphics/gl/Context.hpp>
#include <engine/core/graphics/IWindow.hpp>

#include <engine/core/events/Keys.hpp>
#include <engine/core/events/Mouse.hpp>

#include <engine/core/utils/Config.hpp>

namespace phx
{
	namespace sdl
	{
		/**
		 * @brief Class to use SDL as a Windowing Library. See IWindow documentation for further information.
		 * 
		 */
		class SDLWindow : public phx::gfx::IWindow
		{
		public:
		  	/**
			 * @brief Creates the actual window
			 * 
			 * @param title 	Refer to IWindow documentation
			 * @param width 	Refer to IWindow documentation
			 * @param height 	Refer to IWindow documentation
			 * @param version 	Refer to IWindow documentation
			 * @param profile 	Refer to IWindow documentation
			 */
			SDLWindow(const std::string& title, int width, int height, phx::gfx::GLVersion version, phx::gfx::GLProfile profile);
			~SDLWindow();

			virtual void pollEvents();
			virtual void swapBuffers();
			virtual bool isRunning();
			virtual void close();

			virtual void setTitle(const char *title);
			virtual void getSize(int& width, int& height);
			virtual void setSize(int width, int height);
			virtual void setFullscreen(bool enabled);
			virtual void setResizable(bool enabled);
			virtual void setCursorState(phx::gfx::CursorState cursorState);
	
			virtual void setVSync(bool value);
			virtual void addKeyCallback(events::KeyEventType eventType, events::Keys key, std::function<void()> callback);
			virtual void addMouseMoveCallback(std::function<void(double, double)> callback);
			virtual void addWindowEventCallback(events::WindowEventType eventType, std::function<void()> callback);
	
			virtual void addMouseActionCallback(std::function<void(TVector2<int>, events::MouseAction, events::MouseButton)> callback);

			inline SDL_Window* getSDLWindow() const { return m_window; }

		  	virtual bool isKeyDown(events::Keys key);
		 	virtual TVector2<int> getMousePosition();

		  	virtual void setMousePosition(TVector2<int> newPos);

		private:
			/// @brief A Vector2 to store what size the window was before it was made fullscreen.
			TVector2<int> m_preFullScreenSize = TVector2<int>(0, 0);

			/// @brief The pointer to the window's data.
			SDL_Window* m_window;

			/// @brief The OpenGL context for the data.
			SDL_GLContext m_context;

			/// @brief Boolean to see if it is "still running".
			bool m_running;

			/// @brief Struct for storing KeyEvent callbacks and related data with it.
			struct KeyEvent_t
			{
				int eventType;
				int key;
				std::function<void()> callback;
			};

			struct MouseActionEvent_t
			{
				std::function<void(TVector2<int>, phx::events::MouseAction, phx::events::MouseButton)> callback;
			};

			/// @brief MouseMoveEvent callback "holder". Makes handling the data in the function definitions much easier.
			struct MouseMoveEvent_t
			{
				std::function<void(double,double)> callback;
			};

			/// @brief Window Event callback "holder". Makes handling the data in the function definitions much easier.
			struct WindowEvent_t
			{
				int eventType;
				std::function<void()> callback;
			};

			/// @brief Vector for storing KeyEvents, is cycled through when a key event is received.
			std::vector<KeyEvent_t> m_keyEvents;

			/// @brief Vector for storing MouseMoveEvents, is cycled through when the mouse is moved.
			std::vector<MouseMoveEvent_t> m_mouseMoveEvents;

			/// @brief Vector for storing WindowEvents, is cycled through when there is a window event.
			std::vector<WindowEvent_t> m_windowEvents;

			std::vector<MouseActionEvent_t> m_mouseActionEvents;
		};

	}
}
