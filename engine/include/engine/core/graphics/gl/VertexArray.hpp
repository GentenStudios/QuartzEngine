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
				void bind() const;

				/**
				 * @brief unbind the array, like a wuss.
				 * 
				 */
				void unbind() const;

			private:
				/// @brief Unique ID for the Vertex Array, set by OpenGL
				unsigned int m_arrayID;
			};

		}
	}
}