#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/math/Math.hpp>
#include <quartz/core/events/Event.hpp>
#include <quartz/core/graphics/IWindow.hpp>

#include <vector>
#include <functional>

#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				class QZ_API GLWindow : public gfx::IWindow
				{
				public:
					GLWindow(const std::string& title, int width, int height);
					~GLWindow();

					void pollEvents() override;
					void swapBuffers() const override;

					void registerEventListener(std::function<void(events::Event&)> listener) override;

					void show() const override;
					void hide() const override;
					void maximise() const override;
					void minimise() const override;
					void focus() const override;
					void close() override;
					bool isRunning() const override;

					void resize(math::vec2i size) override;
					void setResizable(bool enabled) override;
					math::vec2i getSize() const override;

					void setVSync(bool enabled) override;
					bool isVSync() const override;

					void setTitle(const std::string& title) const override;

					void setFullscreen(bool enabled) override;
					bool isFullscreen() const override;

					void setCursorState(gfx::CursorState state) override;
					void setCursorPosition(math::vec2 pos) override;
					math::vec2 getCursorPosition() const override;
					bool isKeyDown(int key) const override;

				private:
					SDL_Window* m_window;
					SDL_GLContext m_context;
					bool m_running;

					bool m_vsync;
					bool m_fullscreen;

					math::vec2i m_cachedScreenSize = math::vec2i(0, 0);

					void dispatchToListeners(events::Event&& event)
					{
						for (std::function<void(events::Event&)>& eventListener : m_eventListeners)
						{
							eventListener(event);
						}
					}
				};
			}
		}
	}
}
