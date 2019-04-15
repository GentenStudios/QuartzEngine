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
#include <Quartz/Core/Graphics/API/GL/GLWindow.hpp>
#include <Quartz/Core/Graphics/API/GL/GLCommon.hpp>
#include <Quartz/Core/Utilities/Logger.hpp>

#include <glad/glad.h>

using namespace qz::gfx::api::gl;
using namespace qz::gfx;
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

void GLWindow::dispatchToListeners(const events::Event& event)
{
	for (events::IEventListener* eventListener : m_eventListeners)
	{
		eventListener->onEvent(event);
	}
}

GLWindow::GLWindow(const std::string& title, int width, int height, WindowFlags flags) : m_vsync(false), m_fullscreen(false)
{
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

	int windowOptions = SDL_WINDOW_OPENGL;

	if (hasFlag(flags, WindowFlags::WINDOW_FULLSCREEN))
	{
		windowOptions |= SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS;
		m_fullscreen = true;
	}
	else if (hasFlag(flags, WindowFlags::WINDOW_WINDOWED_FULLSCREEN))
		windowOptions |= SDL_WINDOW_MAXIMIZED;
	else if (hasFlag(flags, WindowFlags::WINDOW_MAXIMIZED))
		windowOptions |= SDL_WINDOW_MAXIMIZED;

	if (hasFlag(flags, WindowFlags::WINDOW_HIDDEN))
		windowOptions |= SDL_WINDOW_HIDDEN;

	if (hasFlag(flags, WindowFlags::WINDOW_RESIZABLE))
		windowOptions |= SDL_WINDOW_RESIZABLE;

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowOptions);
	if (m_window == nullptr)
	{
		LFATAL("Couldn't create window, need OpenGL >= 3.3");
		exit(EXIT_FAILURE);
	}

	if (hasFlag(flags, WindowFlags::WINDOW_VSYNC))
	{
		SDL_GL_SetSwapInterval(1);
		m_vsync = true;
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
	GLint glFlags; glGetIntegerv(GL_CONTEXT_FLAGS, &glFlags);
	if (glFlags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
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
		using namespace events;
		Event e;

		m_gui.pollEvents(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			e.type = EventType::WINDOW_CLOSED; dispatchToListeners(e); m_running = false; break;
		case SDL_MOUSEBUTTONDOWN:
			e.type = EventType::MOUSE_BUTTON_PRESSED; e.mouse.button = static_cast<MouseButtons>(event.button.button);
			e.mouse.x = event.button.x; e.mouse.y = event.button.y;
			break;
		case SDL_MOUSEBUTTONUP:
			e.type = EventType::MOUSE_BUTTON_RELEASED; e.mouse.button = static_cast<MouseButtons>(event.button.button);
			dispatchToListeners(e);
			break;
		case SDL_MOUSEMOTION:
			e.type = EventType::CURSOR_MOVED; e.position.x = event.motion.x; e.position.y = event.motion.y;
			dispatchToListeners(e);
			break;
		case SDL_KEYDOWN:
			e.type = EventType::KEY_PRESSED; e.keyboard.key = static_cast<Keys>(event.key.keysym.scancode);
			e.keyboard.mods = static_cast<Mods>(event.key.keysym.mod); // access these with bitwise operators like AND (&) and OR (|)
			dispatchToListeners(e);
			break;
		case SDL_KEYUP:
			e.type = EventType::KEY_RELEASED; e.keyboard.key = static_cast<Keys>(event.key.keysym.scancode);
			e.keyboard.mods = static_cast<Mods>(event.key.keysym.mod); // access these with bitwise operators like AND (&) and OR (|)
			dispatchToListeners(e);
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
			case SDL_WINDOWEVENT_SIZE_CHANGED:	e.type = EventType::WINDOW_RESIZED; e.size.width = event.window.data1;
				e.size.width = event.window.data1; dispatchToListeners(e);
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:	e.type = EventType::WINDOW_FOCUSED;   dispatchToListeners(e); break;
			case SDL_WINDOWEVENT_FOCUS_LOST:	e.type = EventType::WINDOW_DEFOCUSED; dispatchToListeners(e); break;
			case SDL_WINDOWEVENT_CLOSE:         e.type = EventType::WINDOW_CLOSED;    dispatchToListeners(e); break;
			case SDL_WINDOWEVENT_MINIMIZED:     e.type = EventType::WINDOW_MINIMIZED; dispatchToListeners(e); break;
			case SDL_WINDOWEVENT_MAXIMIZED:     e.type = EventType::WINDOW_MAXIMIZED; dispatchToListeners(e); break;
			case SDL_WINDOWEVENT_RESTORED:      e.type = EventType::WINDOW_RESTORED;  dispatchToListeners(e); break;
			case SDL_WINDOWEVENT_LEAVE:         e.type = EventType::CURSOR_LEFT;      dispatchToListeners(e); break;
			case SDL_WINDOWEVENT_ENTER:         e.type = EventType::CURSOR_ENTERED;   dispatchToListeners(e); break;
			case SDL_WINDOWEVENT_MOVED:         e.type = EventType::WINDOW_MOVED; e.position.x = event.window.data1;
				e.position.y = event.window.data2;    dispatchToListeners(e); break;
			default: break;
			}
		}
	}
}

void GLWindow::swapBuffers() const
{
	SDL_GL_SwapWindow(m_window);
}

void GLWindow::registerEventListener(events::IEventListener* listener)
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

void GLWindow::setTitle(const std::string & title) const
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

void GLWindow::setCursorState(CursorState state)
{
	const bool on = state == CursorState::NORMAL;
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

bool GLWindow::isKeyDown(events::Keys key) const
{
	return SDL_GetKeyboardState(nullptr)[static_cast<SDL_Scancode>(key)];
}

