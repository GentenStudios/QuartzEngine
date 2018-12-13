#include <engine/core/graphics/BatchRenderer.hpp>

using namespace phx::gfx;
using namespace phx;

void BatchRenderer::create(int numVertices)
{
	m_vao = new gl::VertexArray();
	
	m_vbo = new gl::VertexBuffer(gl::BufferTarget::ARRAY_BUFFER, gl::BufferUsage::DYNAMIC_DRAW);
	m_ibo = new gl::VertexBuffer(gl::BufferTarget::ELEMENT_ARRAY_BUFFER, gl::BufferUsage::DYNAMIC_DRAW);

	const int bufferSize = numVertices * sizeof(Vertex3D);

}

void BatchRenderer::destroy()
{
	delete m_vao;
	delete m_vbo;
	delete m_ibo;
}

void BatchRenderer::openBuffer()
{
	m_bufferIsOpen = true;
}

void BatchRenderer::closeBuffer()
{
	m_bufferIsOpen = false;
}