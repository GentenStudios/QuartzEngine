#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace pheonix {
    namespace graphics {

        struct XyData
        {
            int x;
            int y;
        };

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
