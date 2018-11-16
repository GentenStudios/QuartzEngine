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
