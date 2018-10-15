#pragma once

#include "engine/common.hpp"
#include "engine/graphics/opengl/glTypes.hpp"
#include <GL/glew.h>

namespace phoenix {
	namespace graphics {
		namespace opengl {

			struct VertexAttrib
			{
				unsigned int location;	///< Location of attrib, used in shader.
				int components;			///< Number of componenets in the attribute
				GLType type;			///< Attribute Data Type
				int stride;				///< The stride.
				int offset;				///< The Offset

				VertexAttrib(unsigned int attribLocation, int attribNumComp, GLType attribType, int attribStride, int attribOffset) :
					location( attribLocation ),
					components( attribNumComp ),
					type( attribType ),
					stride( attribStride ),
					offset( attribOffset )
				{
					glVertexAttribPointer(location, components, static_cast<GLenum>(attribType), GL_FALSE, attribStride, reinterpret_cast<void*>(offset));
				}

				void enable()
				{
					glEnableVertexAttribArray(location);
				}
			};

		}
	}
}
