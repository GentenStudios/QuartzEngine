/**
 * @file Keys.hpp
 * @brief File for declaring the API for Keys.
 */

#pragma once

#include <SDL.h>

namespace phx {
	namespace events {

		/**
		 * @brief An enum describing the type of EVENT happens when a key is pressed.
		 *
		 */
		enum class KeyEventType : int
		{
			PRESSED,	///< When the key is just *pressed*
			RELEASED,	///< When the key is released.
			REPEAT		///< When the key is pressed repeatedly.
		};

		enum class WindowEventType : int
		{
			RESIZED,
			FOCUS_LOST,
			FOCUS_GAINED,
		};

		/**
		 * @brief Enum for Key aliases, from API to SDL.
		 *
		 * @details This enum is for the Key interface. A key from here can be passed into a function, where it can be casted to INT,
		 *			to get the SDL_Scancode. This is abstract enough that it can be swapped out to another library easily if required at a later date.
		 *
		 *			The underlying type is int, therefore, when writing functions interfacing with this enum, you shouldn't have to cast it if registering the key as an input.
		 *			The casting of the key is already done in SDLWindow.cpp, so it is unnecessary. However, if using the Key differently and require the Scancode for some reason,
		 *			getting the scancode number should be as easy as ``static_cast<int>(events::Keys::KEY_A) (or whatever key...)``
		 */
		enum class Keys : int {
			KEY_A = SDL_SCANCODE_A,
			KEY_B = SDL_SCANCODE_B,
			KEY_C = SDL_SCANCODE_C,
			KEY_D = SDL_SCANCODE_D,
			KEY_E = SDL_SCANCODE_E,
			KEY_F = SDL_SCANCODE_F,
			KEY_G = SDL_SCANCODE_G,
			KEY_H = SDL_SCANCODE_H,
			KEY_I = SDL_SCANCODE_I,
			KEY_J = SDL_SCANCODE_J,
			KEY_K = SDL_SCANCODE_K,
			KEY_L = SDL_SCANCODE_L,
			KEY_M = SDL_SCANCODE_M,
			KEY_N = SDL_SCANCODE_N,
			KEY_O = SDL_SCANCODE_O,
			KEY_P = SDL_SCANCODE_P,
			KEY_Q = SDL_SCANCODE_Q,
			KEY_R = SDL_SCANCODE_R,
			KEY_S = SDL_SCANCODE_S,
			KEY_T = SDL_SCANCODE_T,
			KEY_U = SDL_SCANCODE_U,
			KEY_V = SDL_SCANCODE_V,
			KEY_W = SDL_SCANCODE_W,
			KEY_X = SDL_SCANCODE_X,
			KEY_Y = SDL_SCANCODE_Y,
			KEY_Z = SDL_SCANCODE_Z,

			KEY_1 = SDL_SCANCODE_1,
			KEY_2 = SDL_SCANCODE_2,
			KEY_3 = SDL_SCANCODE_3,
			KEY_4 = SDL_SCANCODE_4,
			KEY_5 = SDL_SCANCODE_5,
			KEY_6 = SDL_SCANCODE_6,
			KEY_7 = SDL_SCANCODE_7,
			KEY_8 = SDL_SCANCODE_8,
			KEY_9 = SDL_SCANCODE_9,
			KEY_0 = SDL_SCANCODE_0,

			KEY_RETURN = SDL_SCANCODE_RETURN,
			KEY_ESCAPE = SDL_SCANCODE_ESCAPE,
			KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,
			KEY_TAB = SDL_SCANCODE_TAB,
			KEY_SPACE = SDL_SCANCODE_SPACE,
			KEY_MINUS = SDL_SCANCODE_MINUS,
			KEY_EQUALS = SDL_SCANCODE_EQUALS,

			KEY_LBRACKET = SDL_SCANCODE_LEFTBRACKET,
			KEY_RBRACKET = SDL_SCANCODE_RIGHTBRACKET,
			KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH,
			KEY_NONUSHASH = SDL_SCANCODE_NONUSHASH,
			KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON,
			KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE,
			KEY_GRAVE = SDL_SCANCODE_GRAVE,
			KEY_COMMA = SDL_SCANCODE_COMMA,
			KEY_PERIOD = SDL_SCANCODE_PERIOD,
			KEY_SLASH = SDL_SCANCODE_SLASH,

			KEY_F1 = SDL_SCANCODE_F1,
			KEY_F2 = SDL_SCANCODE_F2,
			KEY_F3 = SDL_SCANCODE_F3,
			KEY_F4 = SDL_SCANCODE_F4,
			KEY_F5 = SDL_SCANCODE_F5,
			KEY_F6 = SDL_SCANCODE_F6,
			KEY_F7 = SDL_SCANCODE_F7,
			KEY_F8 = SDL_SCANCODE_F8,
			KEY_F9 = SDL_SCANCODE_F9,
			KEY_F10 = SDL_SCANCODE_F10,
			KEY_F11 = SDL_SCANCODE_F11,
			KEY_F12 = SDL_SCANCODE_F12,
			KEY_F13 = SDL_SCANCODE_F13,
			KEY_F14 = SDL_SCANCODE_F14,
			KEY_F15 = SDL_SCANCODE_F15,
			KEY_F16 = SDL_SCANCODE_F16,
			KEY_F17 = SDL_SCANCODE_F17,
			KEY_F18 = SDL_SCANCODE_F18,
			KEY_F19 = SDL_SCANCODE_F19,
			KEY_F20 = SDL_SCANCODE_F20,
			KEY_F21 = SDL_SCANCODE_F21,
			KEY_F22 = SDL_SCANCODE_F22,
			KEY_F23 = SDL_SCANCODE_F23,
			KEY_F24 = SDL_SCANCODE_F24,

			KEY_UP = SDL_SCANCODE_UP,
			KEY_DOWN = SDL_SCANCODE_DOWN,
			KEY_RIGHT = SDL_SCANCODE_RIGHT,
			KEY_LEFT = SDL_SCANCODE_LEFT,

			KEY_KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE,
			KEY_KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY,
			KEY_KP_MINUS = SDL_SCANCODE_KP_MINUS,
			KEY_KP_PLUS = SDL_SCANCODE_KP_PLUS,
			KEY_KP_ENTER = SDL_SCANCODE_KP_ENTER,

			KEY_KP_1 = SDL_SCANCODE_KP_1,
			KEY_KP_2 = SDL_SCANCODE_KP_2,
			KEY_KP_3 = SDL_SCANCODE_KP_3,
			KEY_KP_4 = SDL_SCANCODE_KP_4,
			KEY_KP_5 = SDL_SCANCODE_KP_5,
			KEY_KP_6 = SDL_SCANCODE_KP_6,
			KEY_KP_7 = SDL_SCANCODE_KP_7,
			KEY_KP_8 = SDL_SCANCODE_KP_8,
			KEY_KP_9 = SDL_SCANCODE_KP_9,
			KEY_KP_10 = SDL_SCANCODE_KP_0,

			KEY_LCTRL = SDL_SCANCODE_LCTRL,
			KEY_LSHIFT = SDL_SCANCODE_LSHIFT,
			KEY_LALT = SDL_SCANCODE_LALT,

			KEY_RCTRL = SDL_SCANCODE_RCTRL,
			KEY_RSHIFT = SDL_SCANCODE_RSHIFT,
			KEY_RALT = SDL_SCANCODE_RALT,
		};

	}
}
