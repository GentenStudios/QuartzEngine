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

#include <Quartz/Core/QuartzPCH.hpp>
#include <Quartz/Core/Platform/GLWindow.hpp>
#include <Quartz/Graphics/API/GL/GLCommon.hpp>
#include <Quartz/Core/Events/KeyEvent.hpp>
#include <Quartz/Core/Events/MouseEvent.hpp>
#include <Quartz/Core/Events/ApplicationEvent.hpp>

#include <Quartz/Core/Utilities/Logger.hpp>

#include <glad/glad.h>

using namespace qz::gfx::api::gl;
using namespace qz;

void GLWindow::startFrame()
{
	m_gui.startFrame();
}

void GLWindow::endFrame()
{
	m_gui.endFrame();

	swapBuffers();
	pollEvents();
}

void GLWindow::dispatchToListeners(events::Event&& event)
{
	for (std::function<void(events::Event&)>& eventListener : m_eventListeners)
	{
		eventListener(event);
	}
}

GLWindow::GLWindow(const std::string& title, int width, int height) : m_vsync(false), m_fullscreen(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	#ifdef QZ_DEBUG
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#	endif

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (m_window == nullptr)
	{
		SDL_Quit();
		LFATAL("Couldn't create window, need OpenGL >= 3.3");
		exit(EXIT_FAILURE);
	}

	m_cachedScreenSize = { static_cast<float>(width), static_cast<float>(height) };

	m_context = SDL_GL_CreateContext(m_window);
	SDL_GL_MakeCurrent(m_window, m_context);

	if (!gladLoadGLLoader(static_cast<GLADloadproc>(SDL_GL_GetProcAddress)))
	{
		LFATAL("Failed to initialize GLAD");
		exit(EXIT_FAILURE);
	}

#ifdef QZ_DEBUG
	GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(gfx::api::gl::glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
#endif

	LINFO("---------- OpenGL Details ----------");
	LINFO("Vendor:   ", glGetString(GL_VENDOR));
	LINFO("Renderer: ", glGetString(GL_RENDERER));
	LINFO("Version:  ", glGetString(GL_VERSION));
	LINFO("------------------------------------");

	SDL_ShowWindow(m_window);

	GLCheck(glEnable(GL_DEPTH_TEST));
	GLCheck(glEnable(GL_MULTISAMPLE));

	m_running = true;

	m_gui.init(m_window, &m_context);
}

GLWindow::~GLWindow()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void GLWindow::pollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) > 0)
	{
		m_gui.pollEvents(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			dispatchToListeners(events::WindowCloseEvent());
			m_running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:	
			dispatchToListeners(events::MouseButtonReleasedEvent(static_cast<events::MouseButton>(event.button.button), { static_cast<float>(event.button.x), static_cast<float>(event.button.y) }));
			break;
		case SDL_MOUSEBUTTONUP:		
			dispatchToListeners(events::MouseButtonReleasedEvent(static_cast<events::MouseButton>(event.button.button), { static_cast<float>(event.button.x), static_cast<float>(event.button.y) }));
			break;
		case SDL_MOUSEMOTION:		
			dispatchToListeners(events::MouseMovedEvent({ static_cast<float>(event.motion.x), static_cast<float>(event.motion.y) }));
			break;
		case SDL_KEYDOWN:			
			dispatchToListeners(events::KeyPressedEvent(static_cast<events::Key>(event.key.keysym.scancode), event.key.repeat));
			break;
		case SDL_KEYUP:				
			dispatchToListeners(events::KeyReleasedEvent(static_cast<events::Key>(event.key.keysym.scancode)));
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:		dispatchToListeners(events::WindowResizeEvent(event.window.data1, event.window.data2)); break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:	dispatchToListeners(events::WindowResizeEvent(event.window.data1, event.window.data2)); break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:	dispatchToListeners(events::WindowFocusEvent()); break;
			case SDL_WINDOWEVENT_FOCUS_LOST:	dispatchToListeners(events::WindowLostFocusEvent()); break;
			default: break;
			}
		}
	}
}

void GLWindow::swapBuffers() const
{
	SDL_GL_SwapWindow(m_window);
}

void GLWindow::registerEventListener(std::function<void(events::Event&)> listener)
{
	m_eventListeners.emplace_back(listener);
}

void GLWindow::show() const
{
	SDL_ShowWindow(m_window);
}

void GLWindow::hide() const
{
	SDL_HideWindow(m_window);
}

void GLWindow::maximize() const
{
	SDL_MaximizeWindow(m_window);
}

void GLWindow::minimize() const
{
	SDL_MinimizeWindow(m_window);
}

void GLWindow::focus() const
{
	SDL_SetWindowInputFocus(m_window);
}

void GLWindow::close()
{
	m_running = false;
}

bool GLWindow::isRunning() const
{
	return m_running;
}

void GLWindow::resize(Vector2 size)
{
	SDL_SetWindowSize(m_window, static_cast<int>(size.x), static_cast<int>(size.y));
}

void GLWindow::setResizable(bool enabled)
{
	SDL_SetWindowResizable(m_window, enabled ? SDL_TRUE : SDL_FALSE);
}

Vector2 GLWindow::getSize() const
{
	int x;
	int y;
	SDL_GetWindowSize(m_window, &x, &y);

	return { static_cast<float>(x), static_cast<float>(y) };
}

void GLWindow::setVSync(bool enabled)
{
	m_vsync = enabled;
	SDL_GL_SetSwapInterval(m_vsync ? 1 : 0);
}

bool GLWindow::isVSync() const
{
	return m_vsync;
}

void GLWindow::setTitle(const std::string& title) const
{
	SDL_SetWindowTitle(m_window, title.c_str());
}

void GLWindow::setFullscreen(bool enabled)
{
	m_fullscreen = enabled;

	if (enabled)
	{
		SDL_DisplayMode current;
		const int check = SDL_GetCurrentDisplayMode(0, &current);

		if (check != 0)
		{
			LFATAL("Uh oh! Something went very wrong, send this error message to a developer: ", SDL_GetError());
		}
		else
		{
			m_cachedScreenSize = getSize();
			resize({ static_cast<float>(current.w), static_cast<float>(current.h) });
			SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

			glViewport(0, 0, current.w, current.h);
		}
	}
	else
	{
		SDL_SetWindowFullscreen(m_window, 0);
		resize(m_cachedScreenSize);

		glViewport(0, 0, static_cast<int>(m_cachedScreenSize.x), static_cast<int>(m_cachedScreenSize.y));
	}
}

bool GLWindow::isFullscreen() const
{
	return m_fullscreen;
}

void GLWindow::setCursorState(gfx::CursorState state)
{
	const bool on = state == gfx::CursorState::NORMAL;
	SDL_ShowCursor(on);
}

void GLWindow::setCursorPosition(Vector2 pos)
{
	SDL_WarpMouseInWindow(m_window, static_cast<int>(pos.x), static_cast<int>(pos.y));
}

Vector2 GLWindow::getCursorPosition() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return { static_cast<float>(x), static_cast<float>(y) };
}

bool GLWindow::isKeyDown(events::Key key) const
{
	return SDL_GetKeyboardState(nullptr)[static_cast<SDL_Scancode>(key)];
}

