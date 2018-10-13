#pragma once

#include "engine/common.hpp"

#include <GL/glew.h>

namespace pheonix
{
	namespace graphics
	{
		namespace opengl
		{

			class Buffer
			{
			public:
				/// @brief An Enum of valid Targets for an OpenGL buffer (more will be added as necessary)
				enum class Target
				{
					ARRAY = GL_ARRAY_BUFFER,
					DRAW_INDIRECT = GL_DRAW_INDIRECT_BUFFER,
					DISPATCH_INDIRECT = GL_DISPATCH_INDIRECT_BUFFER,
					ELEMENT = GL_ELEMENT_ARRAY_BUFFER,
					TEXTURE = GL_TEXTURE_BUFFER,
					UNIFORM = GL_UNIFORM_BUFFER
				};

				/// @brief An Enum of valid Usages for an OpenGL buffer (more will be added as needed)
				enum class Usage
				{
					STREAM_DRAW = GL_STREAM_DRAW,
					STATIC_DRAW = GL_STATIC_DRAW,
					DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
				};

				/**
				 * @brief Creates a buffer using the target and usage.
				 * @param target An entry from the Target Enum.
				 * @param usage An entry from the Usage Enum.
				 */
				Buffer( Target target, Usage usage );
				~Buffer();

				/**
				 * @brief Sets a new target for the buffer.
				 * @param target The new target which the buffer is set with.
				 */
				void setTarget( Target target );

				/**
				 * @brief Sets a new usage for the buffer.
				 * @param usage The new usage which the buffer is set with.
				 */
				void setUsage( Usage usage );

				void bind();
				void unbind();

				/**
				 * @brief Set the Buffer data, wraps glBufferData
				 * @param buffer The buffer itself.
				 * @param size The size of the buffer.
				 */
				void setData( void* buffer, int size );

				/**
				 * @brief Sub in Buffer data, wraps glBufferSubData
				 * @param buffer The buffer itself.
				 * @param offset The offset of the data being subbed.
				 * @param size The size of the data being subbed.
				 */
				void subData( void* buffer, int offset, int size );

				/**
				 * @brief Returns the ID of the buffer.
				 * @return unsigned int with the buffers ID.
				 */
				unsigned int getID() const;

			private: 
				unsigned int m_bufferID;

				Target m_target;
				Usage m_usage;

				int m_size;

			};
		}
	}
}
