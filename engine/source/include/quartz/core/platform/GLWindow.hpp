#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/math/Math.hpp>
#include <quartz/core/events/Event.hpp>
#include <quartz/core/graphics/IWindow.hpp>

#include <vector>
#include <functional>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <quartz/core/platform/SDLGuiLayer.hpp>

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

					void resize(Vector2i size) override;
					void setResizable(bool enabled) override;
					Vector2i getSize() const override;

					void setVSync(bool enabled) override;
					bool isVSync() const override;

					void setTitle(const std::string& title) const override;

					void setFullscreen(bool enabled) override;
					bool isFullscreen() const override;

					void setCursorState(gfx::CursorState state) override;
					void setCursorPosition(Vector2 pos) override;
					Vector2 getCursorPosition() const override;
					bool isKeyDown(int key) const override;
					
					void startGUIFrame() override;
					void endGUIFrame() override;

				private:
					SDL_Window* m_window;
					SDL_GLContext m_context;
					SDLGuiLayer m_gui;

					bool m_running;

					bool m_vsync;
					bool m_fullscreen;

					Vector2i m_cachedScreenSize = Vector2i(0, 0);

				private:
					void dispatchToListeners(events::Event&& event);
				};
			}
		}
	}
}
