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
#include <Quartz/Core/Events/EventEnums.hpp>

namespace qz
{
	namespace events
	{
		/**
		 * @brief Derived Class from Event for whenever the mouse is moved.
		 * 
		 * Mouse Move Events require data to be passed on, mainly to indicate the new position of the cursor. This works even if the
		 * cursor has been "disabled" through the windowing class. The mouse position is NOT relative to the previous position, but always
		 * just the position of the mouse within the window. If the mouse positions are required to be relative, you must track the previous
		 * position yourself.
		 */
		class MouseMovedEvent : public Event
		{
		public:
			/**
			 * @brief Constructs a MouseMoved Event.
			 * @param pos The new position of the cursor. NOT relative to the previous cursor position.
			 */
			MouseMovedEvent(const Vector2 pos) : m_mousePos(pos) {}

			/**
			 * @brief Gets the new position of the cursor.
			 * @return The position of the mouse, as a Vector2 providing access through the x, and y, members.
			 */
			Vector2 getPos() const { return m_mousePos; }

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(MOUSE_CURSOR_MOVED);

			/// @brief Automatically "creates" the member function(s) which require the Event's Category(s).
			EVENT_CLASS_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT);

		private:
			Vector2 m_mousePos; /// @brief The 2 Component Vector storing the new cursor position.
		};

		/**
		 * @brief Derived Class from Event for whenever a mouse's scroll wheel is used.
		 * 
		 * Mouse Scroll Events require 1 piece of data, but has two internal pieces. Most mice have scroll wheels that only aid scrolling
		 * up and down, however, some mice allow scrolling sideways, allowing 2 possible pieces of data to be used. These are stored in a
		 * Vector2, with the "x" component being the sideways-scroll offset, and the "y" component being the "normal", up-down-scroll offset.
		 */
		class MouseScrolledEvent : public Event
		{
		public:
			/**
			 * @brief Constructs a MouseScrolled Event.
			 * @param scrollOffset The offset of the scroll wheel on both axis.
			 */
			MouseScrolledEvent(const Vector2 scrollOffset) : m_mouseScrollWheelOffset(scrollOffset) {}

			/**
			 * @brief Gets the offset of the mouse scroll wheel on both axis.
			 * @return A 2 Component Vector containing the values for offsets on both the x and y axis.
			 */
			Vector2 getOffset() const { return m_mouseScrollWheelOffset; };

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(MOUSE_SCROLLED);

			/// @brief Automatically "creates" the member function(s) which require the Event's Category(s).
			EVENT_CLASS_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT);

		private:
			Vector2 m_mouseScrollWheelOffset; /// @brief The actual 2 component vector storing the offsets.
		};

		/**
		 * @brief Derived Class from Event for whenever there is an action upon any Mouse Button.
		 * 
		 * Mouse Button events require two pieces of data. One of those is the button being pressed; currently (as of 20/02/2019), only the main buttons, such as
		 * Left, Right, and Middle are supported. The other piece of data is the position at which the mouse button is pressed/released. this may be useful for GUIs and
		 * similar things, to find if a button was pressed on top of a... button.
		 * 
		 * The mouse position when a button is pressed/released is not always important, as for example, with a camera in a potential voxel game, when the left button 
		 * is clicked, a Ray is casted from the camera position in the direction it's facing. It does NOT actually use the button press/release position.
		 */
		class MouseButtonEvent : public Event
		{
		public:
			/**
			 * @brief Gets the mouse button that has been pressed/released.
			 * @return The mouse button that has been pressed/released, in the form of the MouseButton enumerator.
			 */
			MouseButton getMouseButton() const { return m_button; }

			/**
			 * @brief Gets the position at which the mouse button was pressed/released.
			 * @return A 2 Component Vector with the corresponding x and y members relating to the cursor position at the time of press/release.
			 */
			Vector2 getButtonEventPos() const { return m_buttonEventPos; };

			/// @brief Automatically "creates" the member function(s) which require the Event's Category(s).
			EVENT_CLASS_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT | EventCategory::MOUSE_BUTTON);

		protected:
			/**
			 * @brief Constructs a MouseButton Event.
			 * @param button The Button being pressed/released.
			 * @param pos The position at which the mouse button is pressed/released
			 * 
			 * This constructor is protected so only derived classes can create a MouseButton Event. This is mainly due to the uselessness
			 * of having a custom constructable MouseButton Event, as these only have data, and no reference to what the actual action is.
			 */
			MouseButtonEvent(const MouseButton button, const Vector2 pos) : m_button(button), m_buttonEventPos(pos) {}

			MouseButton m_button; /// @brief The actual button being pressed/released.
			Vector2 m_buttonEventPos; /// @brief The position of the press/release.
		};

		/**
		 * @brief Derived Class from MouseButtonEvent for whenever a Mouse Button is pressed.
		 * 
		 * Mouse Button Presses don't require any extra pieces of data above what is already provided by the MouseButtonEvent parent class. This event is polled and only has
		 * the specialized functions associated with them through the dispatcher called once every game loop when pollEvents() in the Windowing class(es) is called.
		 */
		class MouseButtonPressedEvent : public MouseButtonEvent
		{
		public:
			/**
			 * @brief Constructs a MouseButtonPressed Event.
			 * @param button The button being pressed. This is passed straight onto the parent MouseButtonEvent class.
			 * @param pressPos The position of the cursor when the button is pressed. This is passed straight onto the parent MouseButtonEvent class.
			 */
			MouseButtonPressedEvent(const MouseButton button, const Vector2 pressPos) : MouseButtonEvent(button, pressPos) {}

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED);
		};

		/**
		 * @brief Derived Class from MouseButtonEvent for whenever a MouseButton is released.
		 * 
		 * Mouse Button releases don't require any extra pieces of data above what is already provided by the MouseButtonEvent parent class. This event is polled and only has
		 * the specialized functions associated with them through the dispatcher called once every game loop when pollEvents() in the Windowing class(es) is called.
		 */
		class MouseButtonReleasedEvent : public MouseButtonEvent
		{
		public:
			/**
			 * @brief Constructs a MouseButtonReleased Event.
			 * @param button The actual mouse button being released. This is passed straight onto the parent MouseButtonEvent class.
			 * @param releasePos The cursor position at which the mouse button is released. This is passed straight onto the parent MouseButtonEvent class.
			 */
			MouseButtonReleasedEvent(const MouseButton button, const Vector2 releasePos) : MouseButtonEvent(button, releasePos) {}

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED);
		};
	}
}

