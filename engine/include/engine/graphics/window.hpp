#pragma once

#include "engine/graphics/eventReturnTypes.hpp"

#include <string>
#include <vector>

#include <GLFW/glfw3.h>

namespace pheonix {
    namespace graphics {

        enum class glfwCallbacks
        {
            WINDOWPOS,
            WINDOWSIZE,
            WINDOWCLOSE,

            MOUSEBUTTON,
            CURSORPOS,
            KEY
        };

        class Window
        {
        public:
            Window( int width, int height, std::string title );
            ~Window();

            XyData getCursorPos() const;
            void setCursorPos( XyData pos );

            void defaultHints();
            void hint( int target, int hint );
            void initialiseSystems();
            void swapInterval( int interval );

            bool shouldClose() const;
            void setShouldClose( bool close );
            void swapBuffers();
            void pollEvents();

            XyData getWindowSize() const;
            void setWindowSize( XyData size );
            void setWindowSize( int x, int y );
            void addFunctionCallbacks( glfwCallbacks callback, void (*callback_function)(void) );

        private:
            GLFWwindow* m_window;

        };

    } // namespace graphics
} // namespace pheonix
