#pragma once

#include "engine/graphics/eventReturnTypes.hpp"

#include <string>
#include <GLFW/glfw3.h>

namespace pheonix {
    namespace graphics {

        class Window
        {
        public:
            Window() {}
            ~Window() {}

            XyData getCursorPos() const;
            void setCursorPos( XyData pos );

            void defaultHints();
            void hint( int target, int hint );
            void initialiseSystems();
            void createWindow( int width, int height, std::string& title );
            void makeContextCurrent();
            void destroyWindow();

            inline int shouldClose() const;
            int setShouldClose() const;
            void swapBuffers();
            void pollEvents();

            XyData getWindowSize();
            void setWindowSize( XyData size );
            void setWindowSize( int x, int y );

        private:
            GLFWwindow* m_window;

        };

    } // namespace graphics
} // namespace pheonix
