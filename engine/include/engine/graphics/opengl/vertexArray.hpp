#pragma once

#include "engine/common.hpp"

#include <GL/glew.h>

namespace phoenix
{
	namespace graphics
	{
		namespace opengl
		{

			/**
			 * @brief The VertexArray class for VAOs
			 */
			class VertexArray
			{
			public:
				VertexArray();
				~VertexArray();

				/// @brief Bind the VAO
				void bind();

				/// @brief Unbind the VAO
				void unbind();

			private:
				unsigned int m_arrayID;
			};

		}
	}
}
