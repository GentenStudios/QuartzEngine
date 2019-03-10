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
#include <Quartz/Core/Events/Event.hpp>
#include <Quartz/Core/Events/EventEnums.hpp>

namespace qz
{
	namespace events
	{
		/**
		 * @brief Derived Class from Event for whenever an event involves a key.
		 * 
		 * Key Events do require data to be passed on, however, there is only one piece that both KeyPress and Release events require.
		 * That piece of data is the keycode, which dictates which key that the game things is pressed. This is set by the windowing class as that 
		 * tracks all input. These events are polled like all other events, and are therefore NOT viable solutions for input in things like
		 * Cameras and other modules which require key data on the spot.
		 */
		class QZ_API KeyEvent : public Event
		{
		public:
			/**
			 * @brief Gets the Key which is being referred to.
			 * @return The Key which has an action upon it, in the form of the events::Key enum.
			 */
			Key getKeyCode() const { return m_keyCode; }

			/// @brief Automatically "creates" the member function(s) which require the Event's Category(s)_.
			EVENT_CLASS_CATEGORY(EventCategory::KEYBOARD | EventCategory::INPUT);

		protected:
			/**
			 * @brief Constructs a KeyEvent.
			 * @param keycode The Key which is being pressed. In the form of events::Key
			 * 
			 * This constructor is protected so only derived classes can construct a Key object. This abstract base class does NOT have any event
			 * types associated with it, it does not do *anything* except provide a utility function and its corresponding variable.
			 */
			KeyEvent(const Key keycode) : m_keyCode(keycode) {}

			Key m_keyCode; /// @brief The Keycode itself.
		};

		/**
		 * @brief Derived Class from KeyEvent for whenever a key is pressed.
		 * 
		 * Key Press Events require one more piece of data that a generic KeyEvent does not provide, and that is the repeat count. The repeat count is
		 * the number of times that key has been "repeatedly" pressed, without being released, for example, when you press a key, it prints a letter,
		 * then after a second, it starts to spam the same letter again and again, and you don't have to keep pressing it. This piece of data is often
		 * not required, but it is provided in the slim case that it may be needed.
		 */
		class QZ_API KeyPressedEvent : public KeyEvent
		{
		public:
			/**
			 * @brief Constructs a KeyPressed Event.
			 * @param keycode The Key being pressed, this parameter is passed straight onto the parent KeyEvent class.
			 * @param repeatCount The amount of times this key has been repeated, this is explained in the class description.
			 */
			KeyPressedEvent(const Key keycode, const int repeatCount)
				: KeyEvent(keycode), m_repeatCount(repeatCount) {}

			/**
			 * @brief Gets the number of times the key has been repeated.
			 * @return The number of times the key has been repeated.
			 */
			int getRepeatCount() const { return m_repeatCount; }

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(KEY_PRESSED);

		private:
			int m_repeatCount; /// @brief The repeat count.
		};

		/**
		 * @brief Derived Class from KeyEvent for whenever a key is released.
		 * 
		 * Key Release Events don't require any more data than is provided by the KeyEvent. Key Releases are when a key is released from being pressed down. This
		 * often is not required, however can be useful in certain circumstances, so is there in case.
		 */
		class QZ_API KeyReleasedEvent : public KeyEvent
		{
		public:
			/**
			 * @brief Constructs a KeyReleased Event.
			 * @param keycode The Key being pressed, this parameter is passed straight onto the parent KeyEvent class.
			 */
			KeyReleasedEvent(const Key keycode)
				: KeyEvent(keycode) {}

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(KEY_RELEASED);
		};
	}
}

