#pragma once

#include <glad/glad.h>

namespace qz
{
	namespace gfx
	{
		namespace gl
		{

			/**
			 * @brief An ENUM for converting types to OpenGL types, just a top layer to avoid ugly code in things like the client.
			 * 
			 */
			enum class GLType
			{
				FLOAT	= GL_FLOAT,
				UINT	= GL_UNSIGNED_INT,
				INT		= GL_INT,
				UBYTE	= GL_UNSIGNED_BYTE,
				BYTE	= GL_BYTE,
			};

			/**
			 * @brief An ENUM for converting wanted buffer targets to actual OpenGL Buffer Targets.
			 * 
			 */
			enum class BufferTarget
			{
				ARRAY_BUFFER			= GL_ARRAY_BUFFER,
				COPY_READ_BUFFER		= GL_COPY_READ_BUFFER,
				COPY_WRITE_BUFFER		= GL_COPY_WRITE_BUFFER,
				ELEMENT_ARRAY_BUFFER	= GL_ELEMENT_ARRAY_BUFFER,
				PIXEL_PACK_BUFFER		= GL_PIXEL_PACK_BUFFER,
				PIXEL_UNPACK_BUFFER		= GL_PIXEL_UNPACK_BUFFER,
				SHADER_STORAGE_BUFFER	= GL_SHADER_STORAGE_BUFFER,
				TEXTURE_BUFFER			= GL_TEXTURE_BUFFER,
				UNIFORM_BUFFER			= GL_UNIFORM_BUFFER
			};

			/**
			 * @brief An ENUM for converting wanted buffer usages to actual OpenGL Buffer Usages.
			 * 
			 */
			enum class BufferUsage
			{
				DYNAMIC_COPY = GL_DYNAMIC_COPY,
				DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
				DYNAMIC_READ = GL_DYNAMIC_READ,
				STATIC_COPY = GL_STATIC_COPY,
				STATIC_DRAW = GL_STATIC_DRAW,
				STATIC_READ = GL_STATIC_READ,
			};

			/**
			 * @brief An ENUM for Shader types, this mainly makes it easier for adding shader stages, as not a function is required for each type of shader.
			 * 
			 */
			enum class ShaderType {
				VERTEX_SHADER = GL_VERTEX_SHADER,
				FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
				GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
			};

		}
	}
}
