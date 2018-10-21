#include "engine/graphics/opengl/VertexArray.hpp"

using namespace phx::gfx::gl;

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void VertexArray::bind()
{
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

unsigned int VertexArray::getID()
{
	return m_vertexArrayID;
}