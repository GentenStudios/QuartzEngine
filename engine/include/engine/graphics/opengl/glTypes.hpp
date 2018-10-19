#pragma once

#include "engine/common.hpp"

#include <GL/glew.h>

namespace phoenix
{
	namespace graphics
	{
		namespace opengl
		{
			enum class GLType
			{
				FLOAT = GL_FLOAT,
				INT = GL_INT,
				UINT = GL_UNSIGNED_INT,
				BYTE = GL_BYTE,
				UBYTE = GL_UNSIGNED_BYTE,
				SHORT = GL_SHORT,
				USHORT = GL_UNSIGNED_SHORT,

				TRUE = GL_TRUE,
				FALSE = GL_FALSE
			};

		}
	}
}
