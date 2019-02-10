#pragma once

#include <quartz/core/Core.hpp>

#include <quartz/core/graphics/gl/GLDebug.hpp>
#include <glad/glad.h>

namespace qz
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