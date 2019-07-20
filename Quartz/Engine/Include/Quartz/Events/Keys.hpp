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

#include <Quartz/Utilities/EnumTools.hpp>

#include <SDL.h>

namespace qz
{
	namespace events
	{
		enum class MouseButtons : int
		{
			LEFT,
			RIGHT,
			MIDDLE
		};

		enum class Keys : int
		{
			NONE              = 0,
			KEY_SPACE         = SDL_SCANCODE_SPACE,
			KEY_APOSTROPHE    = SDL_SCANCODE_APOSTROPHE,
			KEY_COMMA         = SDL_SCANCODE_COMMA,
			KEY_MINUS         = SDL_SCANCODE_MINUS,
			KEY_PERIOD        = SDL_SCANCODE_PERIOD,
			KEY_SLASH         = SDL_SCANCODE_SLASH,
			KEY_0             = SDL_SCANCODE_0,
			KEY_1             = SDL_SCANCODE_1,
			KEY_2             = SDL_SCANCODE_2,
			KEY_3             = SDL_SCANCODE_3,
			KEY_4             = SDL_SCANCODE_4,
			KEY_5             = SDL_SCANCODE_5,
			KEY_6             = SDL_SCANCODE_6,
			KEY_7             = SDL_SCANCODE_7,
			KEY_8             = SDL_SCANCODE_8,
			KEY_9             = SDL_SCANCODE_9,
			KEY_SEMICOLON     = SDL_SCANCODE_SEMICOLON,
			KEY_EQUAL         = SDL_SCANCODE_EQUALS,
			KEY_A             = SDL_SCANCODE_A,
			KEY_B             = SDL_SCANCODE_B,
			KEY_C             = SDL_SCANCODE_C,
			KEY_D             = SDL_SCANCODE_D,
			KEY_E             = SDL_SCANCODE_E,
			KEY_F             = SDL_SCANCODE_F,
			KEY_G             = SDL_SCANCODE_G,
			KEY_H             = SDL_SCANCODE_H,
			KEY_I             = SDL_SCANCODE_I,
			KEY_J             = SDL_SCANCODE_J,
			KEY_K             = SDL_SCANCODE_K,
			KEY_L             = SDL_SCANCODE_L,
			KEY_M             = SDL_SCANCODE_M,
			KEY_N             = SDL_SCANCODE_N,
			KEY_O             = SDL_SCANCODE_O,
			KEY_P             = SDL_SCANCODE_P,
			KEY_Q             = SDL_SCANCODE_Q,
			KEY_R             = SDL_SCANCODE_R,
			KEY_S             = SDL_SCANCODE_S,
			KEY_T             = SDL_SCANCODE_T,
			KEY_U             = SDL_SCANCODE_U,
			KEY_V             = SDL_SCANCODE_V,
			KEY_W             = SDL_SCANCODE_W,
			KEY_X             = SDL_SCANCODE_X,
			KEY_Y             = SDL_SCANCODE_Y,
			KEY_Z             = SDL_SCANCODE_Z,
			KEY_LEFT_BRACKET  = SDL_SCANCODE_LEFTBRACKET,
			KEY_RIGHT_BRACKET = SDL_SCANCODE_RIGHTBRACKET,
			KEY_BACKSLASH     = SDL_SCANCODE_BACKSLASH,
			KEY_GRAVE_ACCENT  = SDL_SCANCODE_GRAVE,
			KEY_ESCAPE        = SDL_SCANCODE_ESCAPE,
			KEY_ENTER         = SDL_SCANCODE_RETURN,
			KEY_TAB           = SDL_SCANCODE_TAB,
			KEY_BACKSPACE     = SDL_SCANCODE_BACKSPACE,
			KEY_INSERT        = SDL_SCANCODE_INSERT,
			KEY_DELETE        = SDL_SCANCODE_DELETE,
			KEY_RIGHT         = SDL_SCANCODE_RIGHT,
			KEY_LEFT          = SDL_SCANCODE_LEFT,
			KEY_DOWN          = SDL_SCANCODE_DOWN,
			KEY_UP            = SDL_SCANCODE_UP,
			KEY_PAGE_UP       = SDL_SCANCODE_PAGEUP,
			KEY_PAGE_DOWN     = SDL_SCANCODE_PAGEDOWN,
			KEY_HOME          = SDL_SCANCODE_HOME,
			KEY_END           = SDL_SCANCODE_END,
			KEY_CAPS_LOCK     = SDL_SCANCODE_CAPSLOCK,
			KEY_SCROLL_LOCK   = SDL_SCANCODE_SCROLLLOCK,
			KEY_NUM_LOCK      = SDL_SCANCODE_NUMLOCKCLEAR,
			KEY_PRINT_SCREEN  = SDL_SCANCODE_PRINTSCREEN,
			KEY_PAUSE         = SDL_SCANCODE_PAUSE,
			KEY_F1            = SDL_SCANCODE_F1,
			KEY_F2            = SDL_SCANCODE_F2,
			KEY_F3            = SDL_SCANCODE_F3,
			KEY_F4            = SDL_SCANCODE_F4,
			KEY_F5            = SDL_SCANCODE_F5,
			KEY_F6            = SDL_SCANCODE_F6,
			KEY_F7            = SDL_SCANCODE_F7,
			KEY_F8            = SDL_SCANCODE_F8,
			KEY_F9            = SDL_SCANCODE_F9,
			KEY_F10           = SDL_SCANCODE_F10,
			KEY_F11           = SDL_SCANCODE_F11,
			KEY_F12           = SDL_SCANCODE_F12,
			KEY_F13           = SDL_SCANCODE_F13,
			KEY_F14           = SDL_SCANCODE_F14,
			KEY_F15           = SDL_SCANCODE_F15,
			KEY_F16           = SDL_SCANCODE_F16,
			KEY_F17           = SDL_SCANCODE_F17,
			KEY_F18           = SDL_SCANCODE_F18,
			KEY_F19           = SDL_SCANCODE_F19,
			KEY_F20           = SDL_SCANCODE_F20,
			KEY_F21           = SDL_SCANCODE_F21,
			KEY_F22           = SDL_SCANCODE_F22,
			KEY_F23           = SDL_SCANCODE_F23,
			KEY_F24           = SDL_SCANCODE_F24,
			KEY_KP_0          = SDL_SCANCODE_KP_0,
			KEY_KP_1          = SDL_SCANCODE_KP_1,
			KEY_KP_2          = SDL_SCANCODE_KP_2,
			KEY_KP_3          = SDL_SCANCODE_KP_3,
			KEY_KP_4          = SDL_SCANCODE_KP_4,
			KEY_KP_5          = SDL_SCANCODE_KP_5,
			KEY_KP_6          = SDL_SCANCODE_KP_6,
			KEY_KP_7          = SDL_SCANCODE_KP_7,
			KEY_KP_8          = SDL_SCANCODE_KP_8,
			KEY_KP_9          = SDL_SCANCODE_KP_9,
			KEY_KP_DECIMAL    = SDL_SCANCODE_KP_DECIMAL,
			KEY_KP_DIVIDE     = SDL_SCANCODE_KP_DIVIDE,
			KEY_KP_MULTIPLY   = SDL_SCANCODE_KP_MULTIPLY,
			KEY_KP_SUBTRACT   = SDL_SCANCODE_KP_MINUS,
			KEY_KP_ADD        = SDL_SCANCODE_KP_PLUS,
			KEY_KP_ENTER      = SDL_SCANCODE_KP_ENTER,
			KEY_KP_EQUAL      = SDL_SCANCODE_KP_EQUALS,
			KEY_LEFT_SHIFT    = SDL_SCANCODE_LSHIFT,
			KEY_LEFT_CONTROL  = SDL_SCANCODE_LCTRL,
			KEY_LEFT_ALT      = SDL_SCANCODE_LALT,
			KEY_LEFT_SUPER    = SDL_SCANCODE_LGUI,
			KEY_RIGHT_SHIFT   = SDL_SCANCODE_RSHIFT,
			KEY_RIGHT_CONTROL = SDL_SCANCODE_RCTRL,
			KEY_RIGHT_ALT     = SDL_SCANCODE_RALT,
			KEY_RIGHT_SUPER   = SDL_SCANCODE_RGUI,
			KEY_MENU          = SDL_SCANCODE_MENU
		};

		enum class Mods : int
		{
			MOD_NONE         = 0,           // no mod :(
			MOD_LEFT_SHIFT   = KMOD_LSHIFT, // Left Shift
			MOD_RIGHT_SHIFT  = KMOD_RSHIFT, // Right Shift
			MOD_LEFT_CTRL    = KMOD_LCTRL,  // Left Control
			MOD_RIGHT_CTRL   = KMOD_RCTRL,  // Right Control
			MOD_LEFT_ALT     = KMOD_LALT,   // Left Alt
			MOD_RIGHT_ALT    = KMOD_RALT,   // Right Alt
			MOD_LEFT_SUPER   = KMOD_LGUI,   // Left Super
			MOD_RIGHT_SUPER  = KMOD_RGUI,   // Right Super
			MOD_NUM          = KMOD_NUM,    // Num Lock
			MOD_CAPS         = KMOD_CAPS,   // Caps Lock
			MOD_MODE         = KMOD_MODE,   // AltGr
			MOD_EITHER_SHIFT = KMOD_SHIFT,
			MOD_EITHER_CTRL  = KMOD_CTRL,
			MOD_EITHER_ALT   = KMOD_ALT,
			MOD_EITHER_SUPER = KMOD_GUI,
		};
	} // namespace events
} // namespace qz

ENABLE_BITMASK_OPERATORS (qz::events::Mods);
