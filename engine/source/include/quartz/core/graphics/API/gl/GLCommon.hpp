#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/utilities/Logger.hpp>
#include <quartz/core/graphics/API/GFXTypes.hpp>
#include <quartz/core/graphics/API/IBuffer.hpp>
#include <quartz/core/graphics/API/IShaderPipeline.hpp>
#include <quartz/core/graphics/API/ITexture.hpp>

#include <glad/glad.h>

#ifdef QZ_DEBUG
#	define GLCheck(x) x; qz::gfx::api::gl::checkError(__FILE__, __LINE__);
#else
#	define GLCheck(x) x;
#endif

#ifndef QZ_PLATFORM_WINDOWS
#	define __stdcall
#endif

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				inline void checkError(const char* file, const int line)
				{
					using namespace qz::utils;

					GLenum errorCode;
					while ((errorCode = glGetError()) != GL_NO_ERROR)
					{
						std::string error;
						switch (errorCode)
						{
						case GL_INVALID_ENUM:                  error = "INVALID_ENUM";					break;
						case GL_INVALID_VALUE:                 error = "INVALID_VALUE";					break;
						case GL_INVALID_OPERATION:             error = "INVALID_OPERATION";				break;
						case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW";				break;
						case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW";				break;
						case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY";					break;
						case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
						default:							   error = "UNKNOWN";						break; // Something is seriously wrong, get this fixed.
						}

						Logger::instance()->log(LogVerbosity::WARNING, file, line, "[RENDERING][OPENGL ERROR] ", error);
					}
				}

				/**
				 * @brief OpenGL Debugging output function. THIS FUNCTION IS HANDLED BY OPENGL, AND DOES NOT NEED *ANY* INTERVENTION FROM PROGRAMMERS.
				 *
				 * @param source 		The source of the error, whether it be an API error, or WINDOW SYSTEM error, or maybe even a THIRD PARTY error.
				 * @param type 			The type of error, as in ERROR, or DEPRECATED BEHAVIOUR, or other types of errors that OpenGL recognizes.
				 * @param id 			The ID of the error, this is often very vague and can be quite useless.
				 * @param severity 		The severity of the error, whether it be HIGH, MEDIUM, or LOW severity, or even just a notification.
				 * @param length 		The length of the message. (not used by us.)
				 * @param message 		The message itself.
				 * @param userParam 	Any Parameters we decide to make OpenGL send.
				 *
				 * ALL THESE PARAMETERS ARE SET BY OPENGL, AND ALL FUNCTION CALLS ARE DONE BY OPENGL, DO NOT INTERFERE WITH THIS, OR YOU MAY BREAK DEBUGGING OF OPENGL.
				 */
				inline void __stdcall glDebugOutput(
					GLenum source,
					GLenum type,
					GLuint id,
					GLenum severity,
					GLsizei length,
					const GLchar* message,
					const void* userParam)
				{
					using namespace qz::utils;

					std::stringstream subCategories;
					LogVerbosity verb;

					switch (severity)
					{
					case GL_DEBUG_SEVERITY_HIGH:         subCategories << "[HIGH SEVERITY]";	verb = LogVerbosity::FATAL;		break;
					case GL_DEBUG_SEVERITY_MEDIUM:       subCategories << "[MEDIUM SEVERITY]";	verb = LogVerbosity::WARNING;	break;
					case GL_DEBUG_SEVERITY_LOW:          subCategories << "[LOW SEVERITY]";		verb = LogVerbosity::WARNING;	break;
					case GL_DEBUG_SEVERITY_NOTIFICATION: subCategories << "[NOTIFICATION]";		verb = LogVerbosity::DEBUG;		break;
					default:							 subCategories << "[UNKNOWN]";			verb = LogVerbosity::FATAL;		break; // Something is seriously wrong.
					}

					switch (source)
					{
					case GL_DEBUG_SOURCE_API:             subCategories << "[API]";				break;
					case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   subCategories << "[WINDOW SYSTEM]";	break;
					case GL_DEBUG_SOURCE_SHADER_COMPILER: subCategories << "[SHADER COMPILER]";	break;
					case GL_DEBUG_SOURCE_THIRD_PARTY:     subCategories << "[THIRD PARTY]";		break;
					case GL_DEBUG_SOURCE_APPLICATION:     subCategories << "[APPLICATION]";		break;
					case GL_DEBUG_SOURCE_OTHER:           subCategories << "[OTHER]";			break;
					default:							  subCategories << "[UNKNOWN]";			break; // Something is seriously wrong.
					}

					switch (type)
					{
					case GL_DEBUG_TYPE_ERROR:               subCategories << "[ERROR]";					break;
					case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: subCategories << "[DEPRECATED BEHAVIOUR]";	break;
					case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  subCategories << "[UNDEFINED BEHAVIOUR]";	break;
					case GL_DEBUG_TYPE_PORTABILITY:         subCategories << "[PORTABILITY]";			break;
					case GL_DEBUG_TYPE_PERFORMANCE:         subCategories << "[PERFORMANCE]";			break;
					case GL_DEBUG_TYPE_MARKER:              subCategories << "[MARKER]";				break;
					case GL_DEBUG_TYPE_PUSH_GROUP:          subCategories << "[PUSH GROUP]";			break;
					case GL_DEBUG_TYPE_POP_GROUP:           subCategories << "[POP GROUP]";				break;
					case GL_DEBUG_TYPE_OTHER:               subCategories << "[OTHER]";					break;
					default:								subCategories << "[UNKNOWN]";				break; // Something is seriously wrong.
					}

					subCategories << " ";

					Logger::instance()->log(verb, "OpenGL Debugger", 0, subCategories.str(), message);
				}

				inline GLenum gfxToOpenGL(DataType type)
				{
					switch (type)
					{
					case DataType::INT:		return GL_INT;
					case DataType::FLOAT:	return GL_FLOAT;
					case DataType::BYTE:	return GL_BYTE;
					case DataType::UINT:	return GL_UNSIGNED_INT;
					case DataType::UBYTE:	return GL_UNSIGNED_BYTE;
					}
				
					return GL_INVALID_VALUE;
				}

				inline GLenum gfxToOpenGL(BufferUsage type)
				{
					switch (type)
					{
					case BufferUsage::STATIC:	return GL_STATIC_DRAW;
					case BufferUsage::DYNAMIC:	return GL_DYNAMIC_DRAW;
					}

					return GL_INVALID_VALUE;
				}

				inline GLenum gfxToOpenGL(BufferTarget type)
				{
					switch (type)
					{
					case BufferTarget::ARRAY_BUFFER:	return GL_ARRAY_BUFFER;
					case BufferTarget::INDEX_BUFFER:	return GL_ELEMENT_ARRAY_BUFFER;
					case BufferTarget::TEXTURE_BUFFER:	return GL_TEXTURE_BUFFER;
					case BufferTarget::UNIFORM_BUFFER:	return GL_UNIFORM_BUFFER;
					}

					return GL_INVALID_VALUE;
				}

				inline GLenum gfxToOpenGL(ShaderType type)
				{
					switch (type)
					{
					case ShaderType::VERTEX_SHADER:		return GL_VERTEX_SHADER;
					case ShaderType::FRAGMENT_SHADER:	return GL_FRAGMENT_SHADER;
					}

					return GL_INVALID_VALUE;
				}

				inline GLenum gfxToOpenGL(TexFilter type)
				{
					switch (type)
					{
					case TexFilter::LINEAR:		return GL_LINEAR;
					case TexFilter::NEAREST:	return GL_NEAREST;
					}

					return GL_INVALID_VALUE;
				}

				inline GLenum gfxToOpenGL(TexFormat type)
				{
					switch (type)
					{
					case TexFormat::RGB:	return GL_RGB;
					case TexFormat::RGBA:	return GL_RGBA;
					case TexFormat::BGR:	return GL_BGR;
					case TexFormat::BGRA:	return GL_BGRA;
					}

					return GL_INVALID_VALUE;
				}

				inline GLenum gfxToOpenGL(TexWrap type)
				{
					switch (type)
					{
					case TexWrap::NONE:				return GL_NONE;
					case TexWrap::REPEAT:			return GL_REPEAT;
					case TexWrap::MIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
					case TexWrap::CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
					case TexWrap::CLAMP_TO_BORDER:	return GL_CLAMP_TO_BORDER;
					}

					return GL_INVALID_VALUE;
				}
			}
		}
	}
}
