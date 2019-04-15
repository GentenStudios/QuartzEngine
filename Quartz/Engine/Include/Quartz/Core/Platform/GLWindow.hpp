// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#pragma once

#include <Quartz/Core/Core.hpp>
#include <Quartz/Core/Math/Math.hpp>
#include <Quartz/Core/Events/Event.hpp>
#include <Quartz/Core/Graphics/IWindow.hpp>
#include <Quartz/Core/Platform/SDLGuiLayer.hpp>

#include <SDL.h>

#include <vector>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				/**
				 * @brief Derived Class from IWindow, for producing a window with an OpenGL context.
				 * 
				 * This is used when a window with an OpenGL context is required. For further documentation, refer to
				 * the docs provided with the IWindow class, as GLWindow is only an implementation based on the public
				 * API as defined in IWindow.
				 */
				class GLWindow : public gfx::IWindow
				{
				public:
					GLWindow(const std::string& title, int width, int height, WindowFlags flags);
					~GLWindow();

					RenderingAPI getRenderAPI() const override { return RenderingAPI::OPENGL; }

					void startFrame() override;
					void endFrame() override;

					void pollEvents() override;
					void swapBuffers() const override;

					void registerEventListener(events::IEventListener* listener) override;

					void show() const override;
					void hide() const override;
					void maximize() const override;
					void minimize() const override;
					void focus() const override;
					void close() override;
					bool isRunning() const override;

					void resize(Vector2 size) override;
					Vector2 getSize() const override;
					void setResizable(bool enabled) override;

					void setVSync(bool enabled) override;
					bool isVSync() const override;

					void setTitle(const std::string& title) const override;

					void setFullscreen(bool enabled) override;
					bool isFullscreen() const override;

					void setCursorState(gfx::CursorState state) override;
					void setCursorPosition(Vector2 pos) override;
					Vector2 getCursorPosition() const override;
					bool isKeyDown(events::Keys key) const override;
					
				private:
					SDL_Window* m_window;
					SDL_GLContext m_context;
					SDLGuiLayer m_gui;

					bool m_running;

					bool m_vsync;
					bool m_fullscreen;

					Vector2 m_cachedScreenSize;

				private:
					/// @brief Stores event listeners for the event dispatching system.
					std::vector<events::IEventListener*> m_eventListeners;

					void dispatchToListeners(const events::Event& event);
				};
			}
		}
	}
}

