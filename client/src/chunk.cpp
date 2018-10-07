#include <engine/common.hpp>

#include "client/chunk.hpp"

#include <iostream>

using namespace pheonix::graphics;

static const glm::vec3 CubeVerts[] = {
    // front
    glm::vec3(-1.f,-1.f,-1.f),
    glm::vec3(1.f,-1.f,-1.f),
    glm::vec3(1.f,1.f,-1.f),
    glm::vec3(1.f,1.f,-1.f),
    glm::vec3(-1.f,1.f,-1.f),
    glm::vec3(-1.f,-1.f,-1.f),

    // back
    glm::vec3(-1.f,-1.f,1.f),
    glm::vec3(1.f,-1.f,1.f),
    glm::vec3(1.f, 1.f,1.f),
    glm::vec3(1.f, 1.f,1.f),
    glm::vec3(-1.f, 1.f,1.f),
    glm::vec3(-1.f, -1.f,1.f),

    // left
    glm::vec3(-1.f, 1.f,1.f),
    glm::vec3(-1.f, 1.f,-1.f),
    glm::vec3(-1.f, -1.f,-1.f),
    glm::vec3(-1.f, -1.f,-1.f),
    glm::vec3(-1.f, -1.f,1.f),
    glm::vec3(-1.f, 1.f,1.f),

    // right
    glm::vec3(1.f, 1.f,1.f),
    glm::vec3(1.f, 1.f,-1.f),
    glm::vec3(1.f, -1.f,-1.f),
    glm::vec3(1.f, -1.f,-1.f),
    glm::vec3(1.f, -1.f,1.f),
    glm::vec3(1.f, 1.f,1.f),

    // bottom
    glm::vec3(-1.f, -1.f, -1.f),
    glm::vec3(1.f, -1.f, -1.f),
    glm::vec3(1.f, -1.f,  1.f),
    glm::vec3(1.f, -1.f,  1.f),
    glm::vec3(-1.f, -1.f,  1.f),
    glm::vec3(-1.f, -1.f, -1.f),

    // top
    glm::vec3(-1.f,  1.f, -1.f),
    glm::vec3(1.f,  1.f, -1.f),
    glm::vec3(1.f,  1.f,  1.f),
    glm::vec3(1.f,  1.f,  1.f),
    glm::vec3(-1.f,  1.f,  1.f),
    glm::vec3(-1.f,  1.f, -1.f)
};

static const glm::vec3 CubeVertEmpty[] = {
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
    glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f)
};

Chunk::Chunk() : m_vertArrayObject(0), m_vertBufferObject(0), m_uvBufferObject(0)
{
    // empty
}

void Chunk::populateChunk( unsigned int chunkSize ) {
    unsigned int sizeCubed = chunkSize * chunkSize * chunkSize;

    m_chunkSize = chunkSize;
    m_vertsInChunk = sizeCubed * vertInCube;

    // Set whole array to have, for example, 16 parts inside the vector.
    m_chunkBlocks.resize( chunkSize );

    for (unsigned int x = 0; x < m_chunkBlocks.size(); x++)
    {
        // Set the X (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][0] to m_chunkBlocks[x][15]
        m_chunkBlocks[x].resize( chunkSize );
        for (unsigned int y = 0; y < m_chunkBlocks.size(); y++)
        {
            // Set the Y (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][y][0] to m_chunkBlocks[x][y][15]
            m_chunkBlocks[x][y].resize( chunkSize );
            for (unsigned int z = 0; z < m_chunkBlocks.size(); z++)
            {
                // Set the Z (first vector part, of the trio) to have the actual value of the blocks data. So, you can have m_chunkBlocks[x][y][z] = BlockType::SOLID
                m_chunkBlocks[x][y][z] = BlockType::SOLID;
            }
        }
    }
}

void Chunk::build() {

    if ( m_populated )
        this->clearOpenGL();

    glm::vec3* chunkVertices = new glm::vec3[ m_vertsInChunk ];

    for (int z = 0; z < m_chunkSize; z++)
    {
        for (int y = 0; y < m_chunkSize; y++)
        {
            for (int x = 0; x < m_chunkSize; x++)
            {
                int memOffset = ( x * vertInCube ) + ( m_chunkSize * ( (y * vertInCube) + m_chunkSize * (z * vertInCube) ) );

                std::memcpy( chunkVertices + memOffset, CubeVerts, sizeof( CubeVerts ) );

                for (int face = 0; face < 6; face++)
                {
                    int memOffsetOffest = static_cast<int>( face ) * 6;

                    for (int q = memOffset + memOffsetOffest; q < memOffset + memOffsetOffest + 6; q++)
                    {
                        chunkVertices[q].x += x * 2;
                        chunkVertices[q].y += y * 2;
                        chunkVertices[q].z += z * 2;
                    }
                }
            }
        }
    }

    glGenVertexArrays(1, &m_vertArrayObject);
    glBindVertexArray(m_vertArrayObject);

    glGenBuffers(1, &m_vertBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_vertsInChunk * sizeof(glm::vec3), chunkVertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

}

void Chunk::draw()
{
    build();

    glBindVertexArray(m_vertArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertBufferObject);

    glDrawArrays(GL_TRIANGLES, 0, m_vertsInChunk);
}

void Chunk::clearOpenGL()
{
    glDeleteVertexArrays(1, &m_vertArrayObject);
    glDeleteBuffers(1, &m_vertBufferObject);

    m_populated = true;
}


