#pragma once

#include "engine/common.hpp"
#include "engine/graphics/opengl/glTypes.hpp"
#include <GL/glew.h>

namespace phoenix {
	namespace graphics {
		namespace opengl {

			struct VertexAttrib
			{
				unsigned int location; ///< Location of attrib, used in shader.

				int components; ///< Number of componenets in the attribute

				GLType type; ///< Attribute Data Type

				VertexAttrib( unsigned int attribLocation, int attribNumComp, GLType attribType) : location( attribLocation ), components( attribNumComp ), type( attribType )
				{
				}

				VertexAttrib( unsigned int attribLocation, int attribNumComp ) : VertexAttrib( attribLocation, attribNumComp, GLType::FLOAT )
				{
				}
			};

		}
	}
}
