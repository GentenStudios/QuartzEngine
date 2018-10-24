#pragma once

#include "engine/common.hpp"
#include "engine/math/Vector2.hpp"

#define GLFW_MAIN_HANDLED
#include <GLFW/glfw3.h>
#include <cinttypes>
#include "engine/graphics/Context.hpp"

#include "engine/graphics/IWindow.hpp"

namespace phx
{
	namespace glfw
	{

		class GLFWWindow : public phx::gfx::IWindow
		{
		public:
			GLFWWindow(const char* title, int width, int height, phx::gfx::GLVersion version, phx::gfx::GLProfile profile, uint8_t aaSamples=1);
            ~GLFWWindow();

			virtual void pollEvents();
			virtual void swapBuffers();
			virtual bool isRunning();
			
			virtual void setTitle(const char* title);
			virtual void getSize(int& width, int& height);
			virtual void setFullscreen(bool enabled);
			virtual void setResizable(bool enabled);

            void setVSync(bool value);

			inline GLFWwindow* getGLFWWindow() const { return m_window; }

		private:
			GLFWwindow* m_window;
			int m_width, m_height;
		};

	}
}
