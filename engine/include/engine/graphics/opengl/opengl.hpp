#pragma once

#include <GL/glew.h>

/**
 * @namespace PHX
 * @brief The Main namespace for any PHOENIX-designed piece of code.
 */
namespace phx
{
	/**
	 * @namespace GFX
	 * @brief The Main namespace for GRAPHICAL related functions/classes
	 */
	namespace gfx
	{
		/**
		 * @namespace GL
		 * @brief The Main namespace for the OpenGL rendering code.
		 */
		namespace gl
		{
			/**
			 * @brief The GLType enum to provide independant formatting values, so upgrading to support multiple rendering
			 *			APIs in the future stays easier.
			 */
			enum class GLType
			{
				FLOAT = GL_FLOAT,
				UINT = GL_UNSIGNED_INT,
				INT = GL_INT,
				UBYTE = GL_UNSIGNED_BYTE,
				BYTE = GL_BYTE,
			};

		}
	}
}
