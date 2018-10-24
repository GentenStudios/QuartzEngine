#pragma once

#include "engine/common.hpp"
#include "engine/graphics/opengl/opengl.hpp"

namespace phx
{
	namespace gfx
	{
		namespace gl
		{


			class VertexBuffer
			{
			public:
				VertexBuffer(BufferTarget target, BufferUsage usage);
				~VertexBuffer();

				void bind();
				void unbind();

				void setData(void* buffer, int size);
				void subData(void* buffer, int offset, int size);

				unsigned int getID() const;

			private:
				unsigned int m_bufferID;

				BufferTarget m_target;
				BufferUsage m_usage;

				int m_size;
			};
			
		}
	}
}
