#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/math/Math.hpp>
#include <quartz/core/events/Event.hpp>
#include <quartz/core/graphics/API/Context.hpp>
#include <quartz/core/events/EventEnums.hpp>

#include <vector>
#include <functional>

namespace qz
{
	namespace gfx
	{
		enum class WindowFlags : std::size_t
		{
			RESIZABLE		= 1 << 0,
			SHOWN			= 1 << 1,
			SPLASH_SCREEN	= 1 << 2,
		};

		enum class CursorState : int
		{
			NORMAL,
			HIDDEN,
			DISABLED
		};

		class QZ_API IWindow
		{
		public:
			static IWindow* create(const std::string& title, unsigned int width, unsigned int height, std::size_t flags, RenderingAPI renderingAPI);
			virtual ~IWindow() = default;

			virtual void pollEvents()                             = 0;
			virtual void swapBuffers()                      const = 0;

			virtual void registerEventListener(std::function<void(events::Event&)> listener) = 0;

			virtual void show()                             const = 0;
			virtual void hide()                             const = 0;
			virtual void maximise()                         const = 0;
			virtual void minimise()                         const = 0;
			virtual void focus()                            const = 0;
			virtual void close()                                  = 0;
			virtual bool isRunning()                        const = 0;

			virtual void resize(Vector2 size)                     = 0;
			virtual void setResizable(bool enabled)               = 0;
			virtual Vector2 getSize()                       const = 0;

			virtual void setVSync(bool enabled)                   = 0;
			virtual bool isVSync()                          const = 0;

			virtual void setTitle(const std::string& title)	const = 0;

			virtual void setFullscreen(bool enabled)              = 0;
			virtual bool isFullscreen()                     const = 0;

			virtual void setCursorState(CursorState state)        = 0;
			virtual void setCursorPosition(Vector2 pos)           = 0;
			virtual Vector2 getCursorPosition()             const = 0;
			virtual bool isKeyDown(int key)	                const = 0;
			
			virtual void startGUIFrame()                          = 0;
			virtual void endGUIFrame()                            = 0;

		protected:
			std::vector<std::function<void(events::Event&)>> m_eventListeners;
		};
	}
}
