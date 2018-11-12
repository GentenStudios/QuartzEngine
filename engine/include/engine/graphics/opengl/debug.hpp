#pragma once

#include "engine/common.hpp"

#include <GL/glew.h>

#define RENDER_ERROR(subSectors, message)		phx::Logger::logMessage(__FILE__, __LINE__, std::string("[RENDERING]").append(subSectors), message, phx::LogVerbosity::ERROR)
#define RENDER_WARNING(subSectors, message)		phx::Logger::logMessage(__FILE__, __LINE__, std::string("[RENDERING]").append(subSectors), message, phx::LogVerbosity::WARNING)
#define RENDER_INFO(subSectors, message)		phx::Logger::logMessage(__FILE__, __LINE__, std::string("[RENDERING]").append(subSectors), message, phx::LogVerbosity::INFO)
#define RENDER_DEBUG(subSectors, message)		phx::Logger::logMessage(__FILE__, __LINE__, std::string("[RENDERING]").append(subSectors), message, phx::LogVerbosity::DEBUG)

// MACRO FOR OPENGL DEBUGGING
#ifdef PHX_GL_DEBUG
#	define GLCheck(x) x; phx::gfx::gl::checkError(__FILE__, __LINE__);
#else
#	define GLCheck(x) x;
#endif

#ifndef PHX_OS_WINDOWS
#define __stdcall
#endif

namespace phx
{
	namespace gfx
	{
		namespace gl
		{

			/**
			 * @brief This function is checking for OpenGL errors and prints a message when one is spotted.
			 * @param file The file from which the function was called (should be __FILE__)
			 * @param line The line where the function was called (should be __LINE__)
			 * @return A boolean, to know if we got an error or not
			 */
			inline void checkError(const char* file, int line)
			{
#ifdef PHX_DEBUG
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
#ifndef PHX_OS_WINDOWS  // Doesn't exist on Windows.
					case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
#endif // !PHX_OS_WINDOWS
					}
					RENDER_WARNING("", error.c_str());
				}
#endif  // PHX_DEBUG
			}

			inline void __stdcall glDebugOutput(GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam)
			{
#ifdef PHX_DEBUG
				// ignore non-significant error/warning codes
				if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

				std::stringstream errorOutput;

				switch (source)
				{
				case GL_DEBUG_SOURCE_API:             errorOutput << "[API]"; break;
				case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   errorOutput << "[WINDOW SYSTEM]"; break;
				case GL_DEBUG_SOURCE_SHADER_COMPILER: errorOutput << "[SHADER COMPILER]"; break;
				case GL_DEBUG_SOURCE_THIRD_PARTY:     errorOutput << "[THIRD PARY]"; break;
				case GL_DEBUG_SOURCE_APPLICATION:     errorOutput << "[APPLICATION]"; break;
				case GL_DEBUG_SOURCE_OTHER:           errorOutput << "[OTHER]"; break;
				}

				switch (type)
				{
				case GL_DEBUG_TYPE_ERROR:               errorOutput << "[ERROR]"; break;
				case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: errorOutput << "[DEPRECATED BEHAVIOUR]"; break;
				case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  errorOutput << "[UNDEFINED BEHAVIOUR]"; break;
				case GL_DEBUG_TYPE_PORTABILITY:         errorOutput << "[PORTABILITY]"; break;
				case GL_DEBUG_TYPE_PERFORMANCE:         errorOutput << "[PERFORMANCE]"; break;
				case GL_DEBUG_TYPE_MARKER:              errorOutput << "[MARKER]"; break;
				case GL_DEBUG_TYPE_PUSH_GROUP:          errorOutput << "[PUSH GROUP]"; break;
				case GL_DEBUG_TYPE_POP_GROUP:           errorOutput << "[POP GROUP]"; break;
				case GL_DEBUG_TYPE_OTHER:               errorOutput << "[OTHER]"; break;
				}

				errorOutput << " " << message;

				switch (severity)
				{
				case GL_DEBUG_SEVERITY_HIGH:         RENDER_ERROR("[HIGH SEVERITY]", errorOutput.str()); break;
				case GL_DEBUG_SEVERITY_MEDIUM:       RENDER_WARNING("[MEDIUM SEVERITY]", errorOutput.str()); break;
				case GL_DEBUG_SEVERITY_LOW:          RENDER_WARNING("[LOW SEVERITY]", errorOutput.str()); break;
				case GL_DEBUG_SEVERITY_NOTIFICATION: RENDER_DEBUG("[NOTIFICATION]", errorOutput.str()); break;
				}
#endif // PHX_DEBUG
			}

		}
	}
}
