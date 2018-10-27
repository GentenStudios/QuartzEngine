#include "engine/graphics/opengl/VertexArray.hpp"

using namespace phx::gfx::gl;

VertexArray::VertexArray()
{
	GLCheck(glGenVertexArrays(1, &m_arrayID));
}

void VertexArray::bind()
{
	GLCheck(glBindVertexArray(m_arrayID));
}

void VertexArray::unbind()
{
	GLCheck(glBindVertexArray(0));
}

VertexArray::~VertexArray()
{
	GLCheck(glDeleteVertexArrays(1, &m_arrayID));
}