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

namespace qz
{
	namespace events
	{
		/**
		 * @brief Derived Class from Event for when a window is closed.
		 * 
		 * Closing a window does not require any data to be passed on, thus, does not home any variables or data that can be accessed.
		 * This function shouldn't trigger much in terms of deleting/freeing resources, however can help trigger internal game-specific things
		 * just for convenience. This does NOT have to be used. It is only recommended so a game can properly shut down, or continue being run
		 * properly after the window closes.
		 */
		class QZ_API WindowCloseEvent : public Event
		{
		public:
			WindowCloseEvent() = default;

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(WINDOW_CLOSE);

			/// @brief Automatically "creates" the member function(s) which require the Event's Category(s)_.
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};

		/**
		 * @brief Derived Class from Event for when a window is resized.
		 * 
		 * The window being resized does require data to be passed around, thus, this class is home to two variables containing the new
		 * width and height of the window. These variables can be accessed through the getWidth and getHeight methods, and used for things
		 * such as resizing a camera's projection matrix, or resizing an OpenGL Viewport.
		 */
		class QZ_API WindowResizeEvent : public Event
		{
		public:
			/**
			 * @brief Constructs a WindowResize event.
			 * @param width The new width of a window, this is set by the actual Windowing class, this does NOT need to be done by anything else.
			 * @param height The new height of a window, this is set by the actual Windowing class, this does NOT need to be done by anything else. 
			 */
			WindowResizeEvent(const unsigned int width, const unsigned int height) : m_width(width), m_height(height) {}

			/**
			 * @brief Gets the new width of the window.
			 * @return The new width of the window.
			 */
			unsigned int getWidth() const { return m_width; }

			/**
			 * @brief Gets the new height of the window.
			 * @return The new height of the window.
			 */
			unsigned int getHeight() const { return m_height; }

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(WINDOW_RESIZE);

			/// @brief Automatically "creates" the member function(s) which require the Event's Category(s).
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);

		private:
			unsigned int m_width;  /// @brief This variable stores the new width of the window.
			unsigned int m_height; /// @brief This variable stores the new height of the window.
		};

		/**
		 * @brief Derived Class from Event for when a Window gains focus (when a window is clicked on and regains control of inputs)
		 * 
		 * Focusing does not require any data to be transferred, hence this class does not own any data for specialized functions to use.
		 * Window Focusing is still important as things should lose control of things such as mice once a window has lost focus, and
		 * should retake control of things such as, you guessed it, mice, once a window has regained focus.
		 */
		class QZ_API WindowFocusEvent : public Event
		{
		public:
			/**
			 * @brief Constructs a WindowFocus event.
			 */
			WindowFocusEvent() = default;

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(WINDOW_FOCUS);

			/// @brief Automatically "creates" the member function(s) which require the Event's Category(s).
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};

		/**
		 * @brief Derived Class from Event for when a Window loses focus (when a window is clicked off of and loses control of inputs)
		 * 
		 * Losing focus does not require any data to be passed on, hence this class does not own any data for specialized functions to use.
		 * Losing focus is still important as things should lose control of things such as mice once a window has lost focus, and
		 * should retake control of things such as, you guessed it, mice, once a window has regained focus.
		 */
		class QZ_API WindowLostFocusEvent : public Event
		{
		public:
			/**
			 * @brief Constructs a WindowLostFocus event.
			 */
			WindowLostFocusEvent() = default;

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(WINDOW_LOST_FOCUS);

			/// @brief Automatically "creates" the member function(s) which require the Event's Category(s).
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};

		/**
		 * @brief Derived Class from Event for every time a game loop is run.
		 * 
		 * Each "tick" (for the engine's definition) is the start of a new iteration of the main game loop. This is NOT implemented as of yet,
		 * and may even be removed at a later date if a necessary need/implementation is not necessary or already completed.
		 */
		class QZ_API AppTickEvent : public Event
		{
		public:
			/**
			 * @brief Constructs a AppTick event.
			 */
			AppTickEvent() = default;

			/// @brief Automatically "creates" the member function(s) which require the Event's Type.
			EVENT_CLASS_TYPE(APP_TICK);

			/// @brief Automatically "creates" the member function(s) which require the Event's Category(s).
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};
	}
}

