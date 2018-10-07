#include <engine/common.hpp>

#include "client/chunk.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace pheonix::graphics;

extern const char* vertexShaderSource;
const char* vertexShaderSource = "#version 330 core \n"
                                 "layout (location = 0) in vec3 aPos; \n"
                                 "uniform mat4 model; \n"
                                 "uniform mat4 view; \n"
                                 "uniform mat4 projection; \n"
                                 "void main() \n"
                                 "{ \n"
                                     "gl_Position = projection * view * model * vec4(aPos, 1.0); \n"
                                 "}";

extern const char* fragmentShaderSource;
const char* fragmentShaderSource = "#version 330 core \n"
                                   "out vec4 FragColor; \n"
                                   //"uniform sampler2D texture"
                                   "void main() \n"
                                   "{ \n"
                                       "FragColor = vec4(0.3f, 0.6f, 0.9f, 1.0f);"
                                   "}";

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
        // Set each X index (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][0] to m_chunkBlocks[x][15]
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

    glGenVertexArrays(1, &m_vertArrayObject);
    glBindVertexArray(m_vertArrayObject);

    unsigned int vertexShader;
    vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, nullptr );
    glCompileShader( vertexShader );

    unsigned int fragmentShader;
    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, nullptr );
    glCompileShader( fragmentShader );

    int success;
    char infoLog[512];
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );

    if ( !success ) {
        glGetShaderInfoLog( vertexShader, 512, nullptr, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );

    if ( !success ) {
        glGetShaderInfoLog( fragmentShader, 512, nullptr, infoLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    m_shaderProgram = glCreateProgram();

    glAttachShader( m_shaderProgram, vertexShader );
    glAttachShader( m_shaderProgram, fragmentShader );
    glLinkProgram( m_shaderProgram );

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
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
                int memOffset = ( x * vertInCube ) + (m_chunkSize * ((y * vertInCube) + m_chunkSize * (z * vertInCube)));

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



    glGenBuffers(1, &m_vertBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_vertsInChunk * sizeof(glm::vec3), chunkVertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glm::mat4 projection = glm::mat4( 1.0f );
    projection = glm::perspective( glm::radians( 45.0f ), 1280.f / 720.f, 0.1f, 100.0f );

    glm::mat4 view = glm::lookAt(
        glm::vec3(-50,50,3), // Camera is at (4,3,3), in World Space
        glm::vec3(3,10,3), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

    glm::mat4 model = glm::mat4( 1.0f );

    int modelLoc = glGetUniformLocation( m_shaderProgram, "model" );
    glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );

    int viewLoc = glGetUniformLocation( m_shaderProgram, "view" );
    glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );

    glUniformMatrix4fv( glGetUniformLocation( m_shaderProgram, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );

    glUseProgram( m_shaderProgram ) ;
}

void Chunk::draw()
{
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


