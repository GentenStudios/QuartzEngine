#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/math/Vector2.hpp>

#include <engine/core/graphics/gl/Context.hpp>

#include <cinttypes>
#include <tuple>
#include <vector>
#include <functional>

namespace phx
{
	namespace gfx
	{
		enum class WindowingAPI
		{
			SDL,
			GLFW
		};

		enum class CursorState : int
		{
			DISABLED,
			HIDDEN,
			NORMAL
		};

		enum class EventType : int
		{
			PRESSED,
			RELEASED,
			REPEAT
		};

		class IWindow
		{
		public:
			static IWindow* createWindow(WindowingAPI windowApi, const char* title, int width, int height, GLVersion version, GLProfile profile);

			virtual void pollEvents() = 0;
			virtual void swapBuffers() = 0;
			virtual bool isRunning() = 0;
			virtual void close() = 0;

			virtual void getSize(int& width, int& height) = 0;
			virtual void setTitle(const char* title) = 0;
			virtual void setFullscreen(bool enabled) = 0;
			virtual void setResizable(bool enabled) = 0;
			virtual void setCursorState(CursorState cursorState) = 0;

			virtual void setVSync(bool value) = 0;
			virtual void addKeyCallback(int eventType, int key, std::function<void()> callback) = 0;
			virtual void addMouseMoveCallback(std::function<void(double, double)> callback) = 0;

			virtual bool isKeyDown(int key) = 0;
			virtual TVector2<int> getMousePosition() = 0;
			virtual void setMousePosition(TVector2<int> newPos) = 0;
		};

	}
}
