#include "engine/graphics/opengl/vertexArray.hpp"

using namespace phoenix::graphics::opengl;

VertexArray::VertexArray()
{
    glGenVertexArrays( 1, &m_arrayID );
}

void VertexArray::bind()
{
    glBindVertexArray( m_arrayID );
}

void VertexArray::unbind()
{
    glBindVertexArray( 0 );
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays( 1, &m_arrayID );
}
