#pragma once

#include "engine/graphics/opengl/opengl.hpp"

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
					glVertexAttribPointer(location,
						components,
						static_cast<GLenum>(type),
						GL_FALSE,
						attribStride * sizeof(static_cast<GLenum>(type)),
						reinterpret_cast<void*>(offset * sizeof(static_cast<GLenum>(type)))
					);
				}

				void enable()
				{
					glEnableVertexAttribArray(location);
				}

				void disable()
				{
					glDisableVertexAttribArray(location);
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