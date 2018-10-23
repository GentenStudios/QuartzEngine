#pragma once

#include "../../utils/constants.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

namespace phx
{
	namespace gfx
	{
		namespace gl
		{
            /**
             * @brief This function is checking for OpenGL error and prints a message when one is spotted
             * @param file The file from which the function was called (should be __FILE__)
             * @param line The line where the function was called (should be __LINE__)
             * @return A boolean, to know if we got an error or not
             */
            inline bool checkError(const char* file, int line)
            {
#ifdef PHX_GL_DEBUG
                bool hasError = false;
                GLenum errorCode;
                while ((errorCode = glGetError()) != GL_NO_ERROR)
                {
                    std::string error = "--";
                    switch (errorCode)
                    {
                        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
                        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
                        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
                        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
                        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
                        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
#ifndef PHX_WINDOWS  // does not exist on Windows for some reasons
                        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
#endif
                    }
                    std::cout << (error.c_str()) << " | " << file << " (" << line << ")" << std::endl;
                    hasError = true;
                }
                return hasError;
#else
                return false;
#endif  // PHX_GL_DBUG
            }
        }
    }
}