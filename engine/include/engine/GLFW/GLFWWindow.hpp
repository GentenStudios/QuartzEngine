#pragma once

#include "engine/common.hpp"
#include "engine/math/Vector2.hpp"

#define GLFW_MAIN_HANDLED
#include <GLFW/glfw3.h>
#include "engine/graphics/Context.hpp"

#include "engine/graphics/IWindow.hpp"
#include "engine/events/Keys.hpp"

#include <assert.h>

namespace phx
{
	namespace glfw
	{

		enum class GLFWCursorState
		{
			DISABLED = GLFW_CURSOR_DISABLED,
			HIDDEN = GLFW_CURSOR_HIDDEN,
			NORMAL = GLFW_CURSOR_NORMAL
		};

		class GLFWWindow : public phx::gfx::IWindow
		{
		public:
			GLFWWindow(const char* title, int width, int height, phx::gfx::GLVersion version, phx::gfx::GLProfile profile, uint8_t aaSamples=1);
            ~GLFWWindow();

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

			inline GLFWwindow* getGLFWWindow() const { return m_window; }

			virtual bool isKeyDown(int key) { assert(false);  return true; }
			virtual TVector2<int> getMousePosition() { assert(false);  return { 0, 0 }; }
			virtual void setMousePosition(TVector2<int> newPos) { assert(false); }

		private:
			GLFWwindow* m_window;
			int m_width, m_height;

            void updateKeysCallbacks();

            using WindowResizeCallback_t = std::tuple<
                std::function<void(int, int)>,  // window resize callback
                std::function<void(int, int)>   // user callback for window resizing
            >;

            using KeyboardCallbacks_t = std::vector<
                std::tuple<
                    int,  // event type
                    int,  // key
                    std::function<void()>  // action
                >
            >;

            using MouseMoveCallback_t = std::function<void(double, double)>;

            using Callbacks_t = std::tuple<
                WindowResizeCallback_t,
                KeyboardCallbacks_t,
                MouseMoveCallback_t
            >;
            Callbacks_t m_callbacks;

            static const std::size_t 
				WindowResizeCallbackIndex = 0,
			    WindowResizeCallbackBase = 0,
                WindowResizeCallbackUser = 1,
                KeyboardCallbacksIndex = 1,
                MouseMoveCallback = 2;
		};

	}
}
