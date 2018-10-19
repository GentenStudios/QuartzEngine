#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace phoenix {
	namespace graphics {

		/// @brief A struct to relieve returning multiple values, soon to be replaced by a Vector2
		struct XyData
		{
			int x;
			int y;
		};

		/**
		 * @brief The glfwCallbacks enum for setting event/function callbacks for a GLFW window.
		 * @details This enum is to make it easier to read and write code for binding the callbacks, as it is *significantly* nicer to read, and abstractable.
		 */
		enum class glfwCallbacks
		{
			WINDOWPOS,      ///< The WINDOWPOS callback is called when a window is moved about, usually doesn't matter.
			WINDOWSIZE,     ///< The WINDOWSIZE callback is called whenever a window is resized.
			WINDOWCLOSE,    ///< The WINDOWCLOSE callback is called when... SHOCKER: The window is closed.

			MOUSEBUTTON,    ///< This callback is called when a Mousebutton is pressed
			CURSORPOS,      ///< This callback is called whenever the cursor is moved.
			KEY             ///< This callback is called whenever a key is pressed.
		};

		/**
		 * @brief Represents the current state of the cursor.
		 */
		enum class CursorState
		{
			DISABLED = GLFW_CURSOR_DISABLED,
			HIDDEN = GLFW_CURSOR_HIDDEN,
			NORMAL = GLFW_CURSOR_NORMAL
		};

		/**
		 * @brief Class for Window objects.
		 */
		class Window
		{
		public:
			/**
			 * @brief The window constructor creates a window.
			 * @param width The window width.
			 * @param height The window height
			 * @param title The window title.
			 */
			Window(int width, int height, std::string title);
			~Window();

			/**
			 * @brief Get's the state of the specified keyboard key.
			 * @param key The GLFW_KEY_* macro for this key. See http://www.glfw.org/docs/latest/group__keys.html
			 * @return Return's the state of this key. Either GLFW_PRESS or GLFW_RELEASE.
			 */
			int getKeyState(int key);

			/*
			 * @brief Set's the state of the cursor.
			 * @param state The state to set the cursor to.
			 */
			void setCursorState(CursorState state);

			/**
			 * @brief Gets the cursor position
			 * @return An X and Y value, in the XyData struct.
			 */
			XyData getCursorPos() const;

			/**
			 * @brief Sets the cursor position.
			 * @param pos An X and Y value from the XyDataStruct
			 */
			void setCursorPos(XyData pos);

			/**
			 * @brief Sets the cursor position
			 * @param x The new X coordinate for the cursor
			 * @param y The new Y coordinate for the cursor
			 */
			void setCursorPos(int x, int y);

			/**
			 * @brief Resets the GLFW window to default "settings"
			 */
			void defaultHints();

			/**
			 * @brief Add a window hint to the GLFW window
			 * @param target The target "variable" to set
			 * @param hint The value that the target is set to.
			 */
			void hint(int target, int hint);

			/**
			 * @brief Initialise GLFW
			 */
			void initialiseSystems();

			/**
			 * @brief Set the swap interval, basically, to help enable/disable VSync easily
			 * @param interval The interval, "1" for the vertical sync rate of your screen/monitor, or VSync
			 */
			void swapInterval(int interval);

			/**
			 * @brief Returns whether the window should close or not
			 * @return A boolean for whether the window should close.
			 */
			bool shouldClose() const;

			/**
			 * @brief Set whether the window should close or not.
			 * @param close The boolean to set the window closing variable to.
			 */
			void setShouldClose(bool close);

			/**
			 * @brief Swap the back and front buffers.
			 */
			void swapBuffers();

			/**
			 * @brief Poll the Key/Mouse/Window events.
			 */
			void pollEvents();

			/**
			 * @brief Set the Window Size.
			 * @return An X and Y variable, in the form of the XyData struct.
			 */
			XyData getWindowSize() const;

			/**
			 * @brief Set the Window Size.
			 * @param size The new X and Y size of the window in the form of the XyData struct.
			 */
			void setWindowSize(XyData size);

			/**
			 * @brief Set the Window Size
			 * @param x The new width of the window.
			 * @param y The new height of the window.
			 */
			void setWindowSize(int x, int y);

		private:
			GLFWwindow* m_window;

		};

	} // namespace graphics
} // namespace phoenix
