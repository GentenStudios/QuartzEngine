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

			/**
			 * @brief Class for VertexArrays. Very simple with just binding and unbinding.
			 * 
			 */
			class VertexArray
			{
			public:
				VertexArray();
				~VertexArray();

				/**
				 * @brief BIND THE ARRAY!
				 * 
				 */
				void bind();

				/**
				 * @brief unbind the array, like a wuss.
				 * 
				 */
				void unbind();

			private:
				unsigned int m_arrayID;
			};

		}
	}
}