#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/graphics/gl/GLEnums.hpp>
#include <engine/core/graphics/gl/GLDebug.hpp>
#include <GL/glew.h>

namespace phx
{
	namespace gfx
	{
		namespace gl
		{

			/**
			 * @brief Class for creating and using a vertex buffer.
			 * 
			 */
			class VertexBuffer
			{
			public:
				/**
				 * @brief Generate a new Vertex Buffer Object
				 * 
				 * @param target The target of the buffer, like an Array Buffer, or Uniform Buffer.
				 * @param usage  The usage of the buffer, such as Dynamic Draw, or Static Draw.
				 */
				VertexBuffer(BufferTarget target, BufferUsage usage);
				~VertexBuffer();

				/**
				 * @brief Bind the Vertex Buffer.
				 * 
				 */
				void bind();

				/**
				 * @brief Unbind the Vertex Buffer.
				 * 
				 */
				void unbind();

				/**
				 * @brief Send Data into a GPU Memory Buffer, created by the constructor.
				 * 
				 * @param buffer The buffer data, casted to a void pointer before adding as a parameter.
				 * @param size 	 The size of the buffer, usually, with vectors, the easiest way is to do: sizeof(vectorName[0]) * vectorName.size()
				 */
				void setData(void* buffer, int size);

				/**
				 * @brief Substitute Data in a GPU Memory Buffer, with something else.
				 * 
				 * @param buffer The actual data, casted to a void pointer before adding as a parameter. 
				 * @param offset The offset within the buffer, so something like: sizeof(vectorName[0]) * 20; or something along those lines, IN BYTES.
				 * @param size   The "amount" of data you would like to substitute, in BYTES.
				 */
				void subData(void* buffer, int offset, int size);

				/**
				 * @brief Get the buffer ID
				 * 
				 * @return Buffer ID, ready to use in something else if required.
				 */
				unsigned int getID() const;

			private:
				/// @brief Unique ID for the Vertex Buffer, set by OpenGL.
				unsigned int m_bufferID;

				/// @brief The Desired Target for the Buffer, such as an Array Buffer, or Uniform Buffer.
				BufferTarget m_target;

				/// @brief The Desired Usage of the Buffer, such as STATIC_DRAW/READ or DYNAMIC_DRAW/READ.
				BufferUsage m_usage;

				/// @brief The size of the buffer.
				int m_size;
			};
			
		}
	}
}
