// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <Quartz/Events/Keys.hpp>

#include <SDL.h>

#include <cstring>

namespace qz
{
	namespace events
	{
		struct Position
		{
			int x;
			int y;
		};

		struct Size
		{
			int width;
			int height;
		};

		struct Scroll
		{
			double x;
			double y;
		};

		struct Keyboard
		{
			Keys key;
			Mods mods;
		};

		struct Mouse
		{
			MouseButtons button;
			Mods         mods;
			int          x;
			int          y;
		};

		enum class EventType : int
		{
			NONE,
			WINDOW_MOVED          = SDL_WINDOWEVENT_MOVED,
			WINDOW_RESIZED        = SDL_WINDOWEVENT_SIZE_CHANGED,
			WINDOW_CLOSED         = SDL_QUIT,
			WINDOW_FOCUSED        = SDL_WINDOWEVENT_FOCUS_GAINED,
			WINDOW_DEFOCUSED      = SDL_WINDOWEVENT_FOCUS_LOST,
			WINDOW_MINIMIZED      = SDL_WINDOWEVENT_MINIMIZED,
			WINDOW_MAXIMIZED      = SDL_WINDOWEVENT_MAXIMIZED,
			WINDOW_RESTORED       = SDL_WINDOWEVENT_RESTORED,
			MOUSE_BUTTON_PRESSED  = SDL_MOUSEBUTTONDOWN,
			MOUSE_BUTTON_RELEASED = SDL_MOUSEBUTTONUP,
			MOUSE_WHEEL_SCROLLED  = SDL_QUIT,
			CURSOR_MOVED          = SDL_MOUSEMOTION,
			CURSOR_LEFT           = SDL_WINDOWEVENT_LEAVE,
			CURSOR_ENTERED        = SDL_WINDOWEVENT_ENTER,
			KEY_PRESSED           = SDL_KEYDOWN,
			KEY_RELEASED          = SDL_KEYUP,
		};

		struct Event
		{
			EventType type;

			// This union MUST be used correctly or shit will go south and you
			// might end up with corrupted memory :( We're using a union, so
			// it's sort of like SDLs Event system, and so we don't have a huge
			// amount of painful polymorphism that will end in us having to
			// restart anyway.
			union {
				Position position;
				Size     size;
				Scroll   scroll;
				Keyboard keyboard;
				Mouse    mouse;
			};

			Event ()
			{
				// This is to make sure that *everything* in the struct + it's
				// union is initialized to 0;
				std::memset (this, 0, sizeof (Event));
			}
		};
	} // namespace events
} // namespace qz
