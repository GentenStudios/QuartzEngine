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

				VertexAttrib(unsigned int attribLocation, int attribNumComp, int attribStride, int attribOffset) :
					location(attribLocation),
					components(attribNumComp),
					stride(attribStride),
					offset(attribOffset)
				{
					glVertexAttribPointer(location, components, GL_FLOAT, GL_FALSE, attribStride * sizeof(float), reinterpret_cast<void*>(offset * sizeof(float)));
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