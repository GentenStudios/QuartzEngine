/**
 * @file IWindow.hpp
 * @brief File for Window API selecitons, CursorStates, EventTypes, and the Window creation interface.  
 * 
 */

#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/math/Vector2.hpp>

#include <engine/core/graphics/gl/Context.hpp>

#include <engine/core/events/Keys.hpp>
#include <engine/core/events/Mouse.hpp>

#include <cinttypes>
#include <tuple>
#include <vector>
#include <functional>

namespace phx
{
	namespace gfx
	{
		/**
		 * @brief The state of the cursor.
		 * 
		 */
		enum class CursorState : int
		{
			DISABLED, 	///< Unusable out of the window, and hidden, so the cursor cannot be used like normal at all.
			HIDDEN,		///< Hidden from site but not disabled, so the Cursor CAN move off the window and become useless, most likely will not be needed.
			NORMAL		///< Becomes useable like a normal mouse cursor.
		};

		/**
		 * @brief The interfacing class for creating a window.
		 * 
		 * @details THIS class in particular just returns a pointer to a new window created and allocated on the heap. The window created isn't really a "window", but more like an
		 * 			object of a class, such as SDLWindow.
		 */
		class IWindow
		{
		public:
			/**
			 * @brief Creates an object to create a window dependant on the Windowing library specified.
			 * 
			 * @param title 	The title of the window, can be changed afterwards.
			 * @param width 	The width of the window, can be changed afterwards
			 * @param height 	The height of the window, can be changed afterwards.
			 * @param version 	The OpenGL version that the window should create a context for. 
			 * @param profile 	The OpenGL profile, such as the Compatability profile, or Core profile.
			 * @return IWindow* The respective object for the class depicted by the WindowingAPI parameter.
			 */
			static IWindow* createWindow(const std::string& title, int width, int height, GLVersion version, GLProfile profile);

			/**
			 * @brief Polls events that occur during the game loop.
			 * 
			 * @details This is different for each Windowing API, but the function is called the same, as in reality, they do exactly the same thing.
			 * 			This does not set any variables or anything like such, but rather variables unique to that windowing library, the neither us, or the end user sees.
			 *
			 */
			virtual void pollEvents() = 0;

			/**
			 * @brief Swaps the back and front buffer.
			 * 
			 * @details Basically just what makes frames move on, the back buffer is drawn to by the renderer, then swapped into the front buffer, which is then cleared, and turned into a back buffer,
			 * 			that isn't exactly what it does, just a simple way to explain it, for now.
			 */
			virtual void swapBuffers() = 0;

			/**
			 * @brief Checks whether the window is still running, and thus (loosely) whether the game should keep running.
			 * 
			 * @return False when the window is needs to be quitted, which should "theoretically" quit the game.
			 */
			virtual bool isRunning() = 0;

			/**
			 * @brief Closes the window, useful in scenarios where there might be an error or if the user clicks a specific button.
			 * 
			 */
			virtual void close() = 0;

			/**
			 * @brief Gets the size of the window
			 * 
			 * @param width The memory address of a width variable, so it can be set from within the function.
			 * @param height The memory address of a height variable, so it can be set from within the function.
			 */
			virtual void getSize(int& width, int& height) = 0;

			/**
			 * @brief Sets the size of the window
			 * 
			 * @param resolution The new size that the window needs to be set to.
			 */
			virtual void setSize(int width, int height) = 0;

			/**
			 * @brief Sets the title of the window.
			 * 
			 * @param title The new title that the window should be given
			 */
			virtual void setTitle(const char* title) = 0;

			/**
			 * @brief Makes the window fullscreen, or un-fullscreens it.
			 * 
			 * @param enabled True or False for whether the window should be made fullscreen.
			 */
			virtual void setFullscreen(bool enabled) = 0;

			/**
			 * @brief Sets whether the window should be able to be resized by the user or not.
			 * 
			 * @param enabled True or False to whether the window should be allowed to be resized by the user
			 */
			virtual void setResizable(bool enabled) = 0;

			/**
			 * @brief Sets the Cursor State of the Window.
			 * 
			 * @param cursorState A value from the CursorState Enumurator, the functionality described there is what the window will end up doing.
			 */
			virtual void setCursorState(CursorState cursorState) = 0;

			/**
			 * @brief Enables or disables VSync.
			 * 
			 * @param value True or False to whether VSync should be enabled or not.
			 */
			virtual void setVSync(bool value) = 0;

			/**
			 * @brief Adds a key callback to the window, called when the key is pressed.
			 * 
			 * @param eventType The type of event that happens. (PRESSED, RELEASED, or REPEATED)
			 * @param key The key that is pressed.
			 * @param callback The callback, in the form of a Lambda, which CANNOT have any parameters.
			 */
			virtual void addKeyCallback(events::KeyEventType eventType, events::Keys key, std::function<void()> callback) = 0;

			/**
			 * @brief Adds a mouse move callback to the window. Callback is called - whenever the mouse is moved.
			 * 
			 * @param callback The actual callback, in the form of a Lambda, has two required parameters as doubles, the new mouse x, and mouse y position.
			 */
			virtual void addMouseMoveCallback(std::function<void(double, double)> callback) = 0;

			/**
			 * @brief Adds a Window Event callback to the window. Callback is called - whenever the window is resized, focused, or unfocused.
			 *
			 * @param callback The actual callback, in the form of a Lambda.
			 */
			virtual void addWindowEventCallback(events::WindowEventType eventType, std::function<void()> callback) = 0;

			virtual void addMouseActionCallback(std::function<void(TVector2<int>, events::MouseAction, events::MouseButton)> callback) = 0;

			/**
			 * @brief Checks whether a specific key has been pressed down or not.
			 * 
			 * @param key The key to check for.
			 * @return False for the key not being pressed down, true when it is pressed down.
			 */
			virtual bool isKeyDown(events::Keys key) = 0;

			/**
			 * @brief Gets the position of the mouse.
			 * 
			 * @return A Templated Vector containing ints instead of floats, arranged in the form of MouseX, MouseY. 
			 */
			virtual TVector2<int> getMousePosition() = 0;
			
			/**
			 * @brief Sets the position of the mouse
			 * 
			 * @param newPos A Templated Vector, containing ints instead of floats, arranged in the form of newMouseX, newMouseY.
			 */
			virtual void setMousePosition(TVector2<int> newPos) = 0;
		};

	}
}
