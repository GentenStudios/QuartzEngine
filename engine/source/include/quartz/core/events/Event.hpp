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

#include <quartz/core/Core.hpp>

#include <functional>

namespace qz
{
	namespace events
	{
		/**
		 * @brief Enumerator for the different types of events that can occur in the runtime duration of the engine.
		 */
		enum class EventType
		{
			NONE,			//< NONE is for an event without a specific cause, it shouldn't need to be used, but it's there.
			WINDOW_CLOSE,		//< Used for when a window is closed, it allows a developer to do certain things when a window is closed.
			WINDOW_RESIZE,		//< Used for when a window is resized, this is mainly useful for recalculating projections/viewports for graphics.
			WINDOW_FOCUS,		//< Used for when a window is focused or "clicked back onto". E.g. A camera can be re-enabled when the window is focused.
			WINDOW_LOST_FOCUS,	//< Used for when a window loses focus, or is "clicked off of". E.g. A camera can be disabled when the window loses focus.
			APP_TICK,		//< Used for when a new iteration of the main game loop runs (NOT IMPLEMENTED AS OF 19/02/2019).
			KEY_PRESSED,		//< Used for when a key is pressed, not great for things like cameras, as the event callback will have a little "latency" to it.
			KEY_RELEASED,		//< Used for when a key is released, not great for things like cameras, as the event callback will have a little "latency" to it.
			MOUSE_BUTTON_PRESSED,	//< Used for when a mouse button is pressed.
			MOUSE_BUTTON_RELEASED,	//< Used for when a mouse button is released.
			MOUSE_CURSOR_MOVED,	//< Used for when a mouse is moved.
			MOUSE_SCROLLED		//< Used for when the scroll wheel on a mouse is used.
		};

		/**
		 * @brief Enumerator for the different categories of events that can occur in the runtime duration of the engine.
		 */
		enum EventCategory : int
		{
			NONE = 0,				//< None is for an event with no specific category, it shouldn't need to be used, but it's there.
			APPLICATION		= 1 << 0,	//< Application is used when the application recieves an event. For example, on the resizing of a window, or a render/tick event (both unimplemented).
			INPUT			= 1 << 1,	//< Input is for anything related to a keyboard/mouse or any other input event that can be possible (such as joysticks and controllers in the future).
			KEYBOARD		= 1 << 2,	//< Keyboard is for any keyboard related event, regardless of whether it is a Key Press or Key Release event.
			MOUSE			= 1 << 3,	//< Mouse is for any mouse related event, whether it be a mouse button, scroll wheel, or just movement.
			MOUSE_BUTTON		= 1 << 4,	//< Mouse Button is for mouse button events specifically, so only Mouse Button Releases and/or Presses.
		};

#		define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; } \
										EventType getEventType() const override { return EventType::type; } \

#		define EVENT_CLASS_CATEGORY(category) int getCategoryFlags() const override { return category; }

		/**
		 * @brief Base Class for all event objects, allowing the universal movement of event objects,
		 *		and simplifying dispatching events to various specialized functions.
		 */
		class QZ_API Event
		{
		public:
			virtual ~Event() = default;

			/**
			 * @brief Gets the type of event a specific Event object relates to.
			 * @return The EventType that is relevant to a specific Event object.
			 */
			virtual EventType getEventType() const = 0;


			/**
			 * @brief Gets the EventCategory flags that applies to a specific Event object. The flags from the EventCategory enums are used as bit flags.
			 * @return The "bit-flag" which can be checked for specific values, revealing if an event is part of a specific category.
			 */
			virtual int getCategoryFlags() const = 0;

			/**
			 * @brief Checks whether the event is of a certain category.
			 * @param category The category that needs to be checked for.
			 * @return Returns true if the event is of the specified category, and false if not.
			 */
			bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; }

		protected:
			/**
			 * @brief Lets the event know whether it has been handled or not.
			 */
			bool m_handled = false;

		private:
			friend class EventDispatcher;
		};

		/**
		 * @brief Functionality wrapper to aid calling specialized functions depending on the event.
		 * @description	Usage is like:
		 * @code{.cpp}
		 *		bool Client::onEvent(Event event)
		 *		{
		 *			auto dispatcher = EventDispatcher(event);
		 *
 		 *			dispatcher.dispatch<events::MouseButtonPressedEvent>(std::bind(&Client::onMouseButtonPress, this, std::placeholder::_1))
		 *			dispatcher.dispatch<events::KeyPressedEvent>(std::bind(&Client::onKeyPress, this, std::placeholder::_1))
		 *			dispatcher.dispatch<events::WindowResizedEvent>(std::bind(&Client::onWindowResized, this, std::placeholder::_1))
		 *		}
		 * @endcode
		 *		
		 *	The template parameter is the type of event that is wanted to be dispatched to that specific function. 
		 *	E.g. If the template parameter is events::MouseButtonPressedEvent, the function specified will only be called (with the appropriate data) if the event has
		 *		 an EventType that matches the internal type of the MouseButtonPressedEvent.
		 */
		class QZ_API EventDispatcher
		{
			/**
			 * @brief Alias for an Function which MUST return a boolean and takes a const reference to a specific event.
			 * @tparam T This is usually the specific event class, like events::KeyPressedEvent, or events::MouseButtonPressedEvent.
			 */
			template <typename T>
			using EventFunc = std::function<bool(T&)>;

		public:
			/**
			 * @brief Constructs a dispatcher.
			 * @param event The event that needs to be dispatched.
			 */
			EventDispatcher(Event& event) : m_event(event) {}

			/**
			 * @brief Dispatches the event to the specified function if certain conditions are met.
			 * @tparam T The type of event that the specified function specializes with.
			 * @param func The actual function that should be called if the event matches the type of event the function requires.
			 * @return True if the Event is the right type for the function, False if the event is not the right type and the function is not called.
			 */
			template <typename T>
			bool dispatch(EventFunc<T> func)
			{
				// This is basically just some error checking, in case someone does it wrong, but in reality, this is unnecessary and
				// may be removed later once we can confirm it is unnecessary.
				if (m_event.getEventType() == T::getStaticType())
				{
					// This static cast madness is to cast the generic Event class to the derived class that the Event::getEventType says it is.
					m_event.m_handled = func(*static_cast<T*>(&m_event));
					return true;
				}

				return false;
			}

		private:
			Event& m_event;
		};
	}
}

