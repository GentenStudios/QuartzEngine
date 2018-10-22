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
				enum class Target
				{
					ARRAY				= GL_ARRAY_BUFFER,
					DRAW_INDIRECT		= GL_DRAW_INDIRECT_BUFFER,
					DISPATCH_INDIRECT	= GL_DISPATCH_INDIRECT_BUFFER,
					ELEMENT				= GL_ELEMENT_ARRAY_BUFFER,
					TEXTURE				= GL_TEXTURE_BUFFER,
					UNIFORM				= GL_UNIFORM_BUFFER
				};

				enum class Usage
				{
					STREAM_DRAW			= GL_STREAM_DRAW,
					STATIC_DRAW			= GL_STATIC_DRAW,
					DYNAMIC_DRAW		= GL_DYNAMIC_DRAW,
				};

				struct VertexAttrib
				{
					int index;
					int componentCount;
					int totalSize;
					int offset;
				};

				VertexBuffer(Target target, Usage usage);
				~VertexBuffer();

				void bind();
				void unbind();

				void setData(void* buffer, int size);
				void subData(void* buffer, int offset, int size);

				unsigned int getID() const;

				void addVertexAttrib(int index, int componentCount, int totalSize, int offset);
				void enableVertexAttribs();

			private:
				unsigned int m_bufferID;

				Target m_target;
				Usage m_usage;

				std::vector<VertexAttrib> m_vertexAttribs;

				int m_size;
			};
			
		}
	}
}