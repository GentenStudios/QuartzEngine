#pragma once

#include <engine/core/graphics/gl/VertexArray.hpp>
#include <engine/core/graphics/gl/VertexBuffer.hpp>

#include <engine/core/math/Vector3.hpp>

namespace phx 
{
	namespace gfx
	{
		struct Vertex3D 
		{
			Vector3 Position;
			Color3 Color;
		};

		class BatchRenderer
		{
		private:
			gl::VertexArray *m_vao;

			gl::VertexBuffer *m_vbo;
			gl::VertexBuffer *m_ibo;

			bool m_bufferIsOpen;

		public:
			void create(int numVertices);
			void destroy();

			void openBuffer();
			void closeBuffer();


		};
	}
}