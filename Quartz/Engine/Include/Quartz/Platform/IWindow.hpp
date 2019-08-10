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

#include <Quartz/Events/Event.hpp>
#include <Quartz/Events/IEventListener.hpp>
#include <Quartz/Graphics/RHI/Context.hpp>
#include <Quartz/Math/Math.hpp>

#include <functional>
#include <vector>

namespace qz
{
	namespace gfx
	{
		/**
		 * @brief The flags for when creating a window. Currently unused,
		 * however, is not too difficult to implement.
		 *
		 * These should be used like bitflags, using bitwise operators. They are
		 * currently unimplemented but will be in the near future.
		 */
		enum class WindowFlags : std::size_t
		{
			RESIZABLE = 1 << 0, /// @brief A flag to set whether the window
			                    /// should be resizable or not.
			SHOWN = 1 << 1, /// @brief A flag to set whether the window should
			                /// initially be shown, or left in the background
			                /// until selected by the user.
		};

		/**
		 * @brief The flags for setting the state of the cursor
		 *
		 * This would be used in the function IWindow::setCursorState().
		 */
		enum class CursorState : int
		{
			NORMAL,  /// @brief Sets the cursor back to "normal", visible &
			         /// controllable, not locked to the window at all.
			HIDDEN,  /// @brief Hides the cursor, but allows "normal" use.
			DISABLED /// @brief Disables the cursor, so it isn't visible,
			         /// currently has the same use as HIDDEN, however they mean
			         /// different in different windowing libraries.
		};

		/**
		 * @brief The interfacing class for creating a window.
		 *
		 * This class in particular just returns a pointer to a new window
		 * created and allocated on the heap. The window created isn't really a
		 * "window", but more like an object of a class, such as SDLWindow.
		 */
		class IWindow
		{
		public:
			/**
			 * @brief Creates an object to create a window dependent on the
			 * Windowing library specified.
			 * @param title 	The title of the window, can be changed
			 * afterwards.
			 * @param width 	The width of the window, can be changed
			 * afterwards
			 * @param height 	The height of the window, can be changed
			 * afterwards.
			 * @return IWindow* The respective object for the class depicted by
			 * the WindowingAPI parameter.
			 */
			static IWindow* create(const std::string& title, unsigned int width,
			                       unsigned int height, std::size_t flags,
			                       RenderingAPI renderingAPI);

			virtual ~IWindow() = default;

			/**
			 * @brief Polls events that occur during the game loop.
			 *
			 * This is different for each Windowing API, but the function is
			 * called the same, as in reality, they do exactly the same thing.
			 * This does not set any variables or anything like such, but rather
			 * variables unique to that windowing library, the neither us, or
			 * the end user sees.
			 *
			 */
			virtual void pollEvents() = 0;

			/**
			 * @brief Swaps the back and front buffer.
			 *
			 * Basically just what makes frames move on, the back buffer is
			 * drawn to by the renderer, then swapped into the front buffer,
			 * which is then cleared, and turned into a back buffer, that isn't
			 * exactly what it does, just a simple way to explain it, for now.
			 */
			virtual void swapBuffers() const = 0;

			/**
			 * @brief Registers/Adds an event listener to the event system of
			 * the window.
			 * @param listener A lambda function which binds the member function
			 * which handles events, and the object it originates from.
			 *
			 * It can be used like:
			 *
			 * @code{.cpp}
			 * (assuming you're adding an event listener from within the target
			 * class.)
			 * window->registerEventListener(std::bind(&Client::onEvent), this,
			 * std::placeholders::_1);
			 * @endcode
			 *
			 * OR
			 *
			 * @code{.cpp}
			 * (assuming you're adding an event listener for a class from
			 * ANOTHER class.)
			 * window->registerEventListener(std::bind(&FPSCamera::onEvent,
			 * m_camera, std::placeholders::_1));
			 * @endcode
			 *
			 * OR
			 *
			 * @code{.cpp}
			 * (assuming you're adding an event listener that doesn't have a
			 * class, but is just a sole function)
			 * window->registerEventListener(&functionName);
			 * @endcode
			 */
			virtual void registerEventListener(
			    events::IEventListener* listener) = 0;

			/**
			 * @brief Shows the window to the user.
			 *
			 * This function will usually just bring the window to the front of
			 * the Window Manager's window stack to show itself to the user.
			 */
			virtual void show() const = 0;

			/**
			 * @brief Hides the window from the user.
			 *
			 * This function will usually just hide the window through using a
			 * function in an OS' Window Manager.
			 */
			virtual void hide() const = 0;

			/**
			 * @brief Maximizes the window.
			 */
			virtual void maximize() const = 0;

			/**
			 * @brief Minimizes the window.
			 */
			virtual void minimize() const = 0;

			/**
			 * @brief Focuses the window.
			 *
			 * This will bring the window to the front of the window stack, and
			 * will also take control of the input mechanisms of a computer
			 * (such as a keyboard/mouse).
			 */
			virtual void focus() const = 0;

			/**
			 * @brief Closes the window
			 */
			virtual void close() = 0;

			/**
			 * @brief Gets the status of the window, and whether it is still
			 * running or not.
			 * @return True if the window is still running, false if not.
			 */
			virtual bool isRunning() const = 0;

			/**
			 * @brief Resizes the window to the size requested.
			 * @param size The new size of window wanted.
			 */
			virtual void resize(Vector2 size) = 0;

			/**
			 * @brief Sets whether the window should be resizable or not.
			 * @param enabled True if the window should be resizable, false if
			 * not.
			 */
			virtual void setResizable(bool enabled) = 0;

			/**
			 * @brief Gets the size of the window.
			 * @return The size of the window, as a Vector2
			 */
			virtual Vector2 getSize() const = 0;

			/**
			 * @brief Sets whether the window should VSync for frame timing or
			 * not.
			 * @param enabled True if the window should use VSync, false if not.
			 */
			virtual void setVSync(bool enabled) = 0;

			/**
			 * @brief Checks whether the window is using VSync or not.
			 * @return
			 */
			virtual bool isVSync() const = 0;

			/**
			 * @brief Sets the title of the window.
			 * @param title The new title of the window.
			 */
			virtual void setTitle(const std::string& title) const = 0;

			/**
			 * @brief Sets the window to fullscreen, or gets the window out of
			 * fullscreen.
			 * @param enabled True if the window should be made fullscreen,
			 * false if it should be taken to the previous window size.
			 */
			virtual void setFullscreen(bool enabled) = 0;

			/**
			 * @brief Checks if the window is fullscreen or not.
			 * @return True if the window is fullscreen, false if not.
			 */
			virtual bool isFullscreen() const = 0;

			/**
			 * @brief Sets the state of the cursor.
			 * @param state The new desired state of the cursor
			 */
			virtual void setCursorState(CursorState state) = 0;

			/**
			 * @brief Sets the position of the cursor.
			 * @param pos The new position of the cursor, in the form of a
			 * Vector2
			 */
			virtual void setCursorPosition(Vector2 pos) = 0;

			/**
			 * @brief Gets the position of the cursor.
			 * @return The cursor of the cursor, in the form of a Vector2
			 */
			virtual Vector2 getCursorPosition() const = 0;

			/**
			 * @brief Checks if whether a certain key is down or not.
			 * @param key The key that needs to be checked.
			 * @return True if the key is being pressed, false if not.
			 */
			virtual bool isKeyDown(events::Keys key) const = 0;

			/**
			 * @brief Calls specific functions which should be ready for the
			 * start of a frame.
			 *
			 * This currently only initializes a new frame for the GUI, however
			 * will do much more at a later date.
			 */
			virtual void startFrame() = 0;

			/**
			 * @brief Calls specific functions which should be done at the end
			 * of a frame.
			 *
			 * This currently ends the GUIs frame, swaps the front and back
			 * graphics buffer, and then polls all events. It may do more at a
			 * future date, but it is VERY important that this function is
			 * called at the end of EACH iteration of the main game loop.
			 */
			virtual void endFrame() = 0;

		protected:
			/// @brief Stores event listeners for the event dispatching system.
			std::vector<events::IEventListener*> m_eventListeners;
		};
	} // namespace gfx
} // namespace qz
