#include <quartz/core/graphics/BatchRenderer.hpp>
#include <quartz/core/graphics/gl/VertexAttrib.hpp>

#include <assert.h>

using namespace qz::gfx;
using namespace qz;

void BatchRenderer::create(int numVertices, int numIndices, gl::ShaderPipeline& shader)
{
	GLCheck(glEnable(GL_BLEND));
	GLCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	shader.use();

	shader.bindAttributeLocation("a_position", 0);
	shader.bindAttributeLocation("a_color", 1);

	m_vao = new gl::VertexArray();
	m_vao->bind();
	
	const int bufferSize = numVertices * sizeof(Vertex3D);
	
	m_vbo = new gl::VertexBuffer(gl::BufferTarget::ARRAY_BUFFER, gl::BufferUsage::DYNAMIC_DRAW);
	m_vbo->bind();
	m_vbo->setData(nullptr, bufferSize);

	m_ibo = new gl::VertexBuffer(gl::BufferTarget::ELEMENT_ARRAY_BUFFER, gl::BufferUsage::DYNAMIC_DRAW);
	m_ibo->bind();
	m_ibo->setData(nullptr, numIndices);
	
	gl::VertexAttrib posAttrib(0, 3, sizeof(Vertex3D), 0, gl::GLType::FLOAT);
	posAttrib.enable();

	gl::VertexAttrib colorAttrib(1, 3, sizeof(Vertex3D), offsetof(Vertex3D, color), gl::GLType::FLOAT);
	colorAttrib.enable();

	m_indexCount = 0;
	m_bufferIsOpen = false;
}

void BatchRenderer::addVertex(const Vertex3D& vertex)
{
	assert(m_bufferIsOpen);

	*(m_vertexBuffer++) = vertex;
}

void BatchRenderer::addIndex(unsigned index)
{
	assert(m_bufferIsOpen);

	*(m_indexBuffer++) = index;

	m_indexCount += 1;
}

bool BatchRenderer::isReadyForDrawing() const
{
	return m_bufferIsOpen;
}

void BatchRenderer::destroy()
{
	delete m_vao;
	delete m_vbo;
	delete m_ibo;
}

void BatchRenderer::openBuffer()
{
	assert(!m_bufferIsOpen);

	m_bufferIsOpen = true;

	m_vao->bind();
	m_vertexBuffer = m_vbo->mapPointer<Vertex3D>();
	m_indexBuffer = m_ibo->mapPointer<unsigned>();
}

void BatchRenderer::closeBuffer()
{
	assert(m_bufferIsOpen);
	m_bufferIsOpen = false;

	m_vbo->unmapPointer();
	m_ibo->unmapPointer();
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;

	m_vao->unbind();
}

void BatchRenderer::draw()
{
	m_vao->bind();
	m_ibo->bind();

	GLCheck(glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr));
	m_indexCount = 0;
	
	m_ibo->unbind();
	m_vao->unbind();

	GLCheck(glDisable(GL_BLEND));
}