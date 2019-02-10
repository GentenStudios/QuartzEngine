#pragma once

#include <quartz/core/graphics/gl/GLEnums.hpp>
#include <quartz/core/graphics/gl/GLDebug.hpp>
#include <glad/glad.h>

namespace qz
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
					m_location(attribLocation),
					m_components(attribNumComp),
					m_stride(attribStride),
					m_offset(attribOffset)
				{
					GLCheck(glVertexAttribPointer(m_location,
						m_components,
						static_cast<GLenum>(type),
						GL_FALSE,
						attribStride,
						reinterpret_cast<void*>(m_offset)
					));
				}

				/**
				 * @brief Enable the Vertex Attribute
				 * 
				 */
				void enable() const
				{
					GLCheck(glEnableVertexAttribArray(m_location));
				}

				/**
				 * @brief Disable the Vertex Attribute
				 * 
				 */
				void disable() const
				{
					GLCheck(glDisableVertexAttribArray(m_location));
				}

			private:
				// Look at VertexAttrib documentation to understand what these do.

				unsigned int m_location;
				int m_components;
				int m_stride;
				int m_offset;
			};

		}
	}
}
