#pragma once

#include <engine/core/graphics/gl/GLEnums.hpp>
#include <engine/core/graphics/gl/GLDebug.hpp>
#include <GL/glew.h>

namespace phx
{
	namespace gfx
	{
		namespace gl
		{
			
			/**
			 * @brief Class for creating Vertex Attrib Pointers
			 * 
			 */
			class VertexAttrib
			{
			public:
				/**
				 * @brief Create a new Vertex Attribute
				 * 
				 * @param attribLocation The location of the attribute, the one in the shaders [so like layout (location = 0)]
				 * @param attribNumComp  The number of components in each part.
				 * @param attribStride 	 The Stride between each part.
				 * @param attribOffset 	 The offset from the beginning of the buffer.
				 * @param type 			 The type of data that each component uses, such as a float, or int.
				 */
				VertexAttrib(unsigned int attribLocation, int attribNumComp, int attribStride, int attribOffset, GLType type) :
					location(attribLocation),
					components(attribNumComp),
					stride(attribStride),
					offset(attribOffset)
				{
					GLCheck(glVertexAttribPointer(location,
						components,
						static_cast<GLenum>(type),
						GL_FALSE,
						attribStride * sizeof(static_cast<GLenum>(type)),
						reinterpret_cast<void*>(offset * sizeof(static_cast<GLenum>(type)))
					));
				}

				/**
				 * @brief Enable the Vertex Attribute
				 * 
				 */
				void enable()
				{
					GLCheck(glEnableVertexAttribArray(location));
				}

				/**
				 * @brief Disable the Vertex Attribute
				 * 
				 */
				void disable()
				{
					GLCheck(glDisableVertexAttribArray(location));
				}

			private:
				// Look at VertexAttrib documentation to understand what these do.

				unsigned int location;
				int components;
				int stride;
				int offset;
			};

		}
	}
}
