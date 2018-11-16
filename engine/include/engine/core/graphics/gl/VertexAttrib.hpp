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

			class VertexAttrib
			{
			public:

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

				void enable()
				{
					GLCheck(glEnableVertexAttribArray(location));
				}

				void disable()
				{
					GLCheck(glDisableVertexAttribArray(location));
				}

			private:
				unsigned int location;
				int components;
				int stride;
				int offset;
			};

		}
	}
}