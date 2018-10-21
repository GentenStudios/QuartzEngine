#include "engine/common.hpp"

#include "engine/graphics/opengl/opengl.hpp"

namespace phx
{
	namespace gfx
	{
		namespace gl
		{

			class VertexArray
			{
			public:
				VertexArray();
				~VertexArray();

				void bind();
				void unbind();

			private:
				unsigned int m_arrayID;
			};

		}
	}
}