#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/graphics/gl/GLDebug.hpp>
#include <GL/glew.h>

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