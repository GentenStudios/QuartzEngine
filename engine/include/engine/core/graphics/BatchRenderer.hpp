#pragma once

#include <engine/core/graphics/gl/VertexArray.hpp>
#include <engine/core/graphics/gl/VertexBuffer.hpp>
#include <engine/core/graphics/gl/ShaderPipeline.hpp>

#include <engine/core/math/Vector3.hpp>

namespace phx 
{
	namespace gfx
	{
		struct Vertex3D 
		{
			Vector3 position;
			Color3 color;

			Vertex3D(const Vector3& pos, const Color3& col)
				: position(pos), color(col) {}
		};

		class BatchRenderer
		{
		private:
			gl::VertexArray *m_vao;

			gl::VertexBuffer *m_vbo;
			gl::VertexBuffer *m_ibo;

			Vertex3D *m_vertexBuffer;
			unsigned *m_indexBuffer;

			size_t m_indexCount;

			bool m_bufferIsOpen;
		public:
			void create(int numVertices, int numIndices, gl::ShaderPipeline& shader);
			void destroy();

			void openBuffer();
			void closeBuffer();

			void draw();

			void addVertex(const Vertex3D& vertex);
			void addIndex(unsigned index);

			bool isReadyForDrawing() const { return m_bufferIsOpen; }
		};
	}
}