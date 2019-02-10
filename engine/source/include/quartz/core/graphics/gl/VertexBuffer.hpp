#pragma once

#include <quartz/core/Core.hpp>

#include <quartz/core/graphics/gl/GLEnums.hpp>
#include <quartz/core/graphics/gl/GLDebug.hpp>
#include <glad/glad.h>

namespace qz
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
				void bind() const;

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

				/*
				 * @brief Get (map) a pointer to the writable location of this GPU buffer. This pointer should be released with `unmapPointer` when it is used.
				 *
				 * @return A pointer to the writable GPU memory represented by this buffer. Unmap this pointer with `unmapPointer`. Can return null
				 */
				template <typename T>
				T* mapPointer()
				{
					bind();

					T* data = (T*)GLCheck(glMapBuffer(static_cast<GLenum>(m_target), GL_WRITE_ONLY));

					return data;
				}

				/*
				 * @brief Unmap the pointer that has been mapped by `mapPointer`. Do not call if `mapPointer` has not already been called.
				 */
				void unmapPointer();

				/*
				 * @brief Get the size of this buffer (in bytes)
				 * 
				 * @return The size of this buffer, in bytes.
				 */
				int getSize() const;

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
