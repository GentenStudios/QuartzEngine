#include <engine/common.hpp>

#include <engine/graphics/opengl/vertexAttrib.hpp>
#include "client/chunk.hpp"

#include <engine/math/vector3.hpp>
#include <engine/math/vector2.hpp>
#include <engine/math/matrix4x4.hpp>

#include <iostream>
#include <cstring>

using namespace phoenix::graphics;
using namespace phoenix;

extern const char* vertexShaderSource;
const char* vertexShaderSource = "#version 330 core \n"
								 "layout (location = 0) in vec3 aPos; \n"
								 "layout (location = 1) in vec2 aUV; \n"
								 "uniform mat4 model; \n"
								 "uniform mat4 view; \n"
								 "uniform mat4 projection; \n"
								 "out vec2 UV; \n"
								 "void main() \n"
								 "{ \n"
								 "gl_Position = projection * view * model * vec4(aPos, 1.0); \n"
								 "UV = aUV; \n"
								 "}";

extern const char* fragmentShaderSource;
const char* fragmentShaderSource = "#version 330 core \n"
								   "out vec4 FragColor; \n"
								   "in vec2 UV; \n"
								   "uniform sampler2D theTexture; \n"
								   "uniform sampler2D theTexture2; \n"
								   "void main() \n"
								   "{ \n"
								   "FragColor = mix( texture(theTexture, UV), texture(theTexture2, UV), 0.5 );\n"
								   "}";

static const Vector3 CubeVerts[] = {
	// front
	Vector3(-1.f,-1.f,-1.f),
	Vector3(1.f,-1.f,-1.f),
	Vector3(1.f,1.f,-1.f),
	Vector3(1.f,1.f,-1.f),
	Vector3(-1.f,1.f,-1.f),
	Vector3(-1.f,-1.f,-1.f),

	// back
	Vector3(-1.f,-1.f,1.f),
	Vector3(1.f,-1.f,1.f),
	Vector3(1.f, 1.f,1.f),
	Vector3(1.f, 1.f,1.f),
	Vector3(-1.f, 1.f,1.f),
	Vector3(-1.f, -1.f,1.f),

	// left
	Vector3(-1.f, 1.f,1.f),
	Vector3(-1.f, 1.f,-1.f),
	Vector3(-1.f, -1.f,-1.f),
	Vector3(-1.f, -1.f,-1.f),
	Vector3(-1.f, -1.f,1.f),
	Vector3(-1.f, 1.f,1.f),

	// right
	Vector3(1.f, 1.f,1.f),
	Vector3(1.f, 1.f,-1.f),
	Vector3(1.f, -1.f,-1.f),
	Vector3(1.f, -1.f,-1.f),
	Vector3(1.f, -1.f,1.f),
	Vector3(1.f, 1.f,1.f),

	// bottom
	Vector3(-1.f, -1.f, -1.f),
	Vector3(1.f, -1.f, -1.f),
	Vector3(1.f, -1.f,  1.f),
	Vector3(1.f, -1.f,  1.f),
	Vector3(-1.f, -1.f,  1.f),
	Vector3(-1.f, -1.f, -1.f),

	// top
	Vector3(-1.f,  1.f, -1.f),
	Vector3(1.f,  1.f, -1.f),
	Vector3(1.f,  1.f,  1.f),
	Vector3(1.f,  1.f,  1.f),
	Vector3(-1.f,  1.f,  1.f),
	Vector3(-1.f,  1.f, -1.f)
};

static const Vector3 CubeVertEmpty[] = {
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f)
};

static const Vector2 CubeUV[] = {
	// front
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),

	// back
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),

	// left
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),

	// right
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),

	// bottom
	Vector2(0.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(0.f, 0.f),
	Vector2(0.f, 1.f),

	// top
	Vector2(0.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(0.f, 0.f),
	Vector2(0.f, 1.f)
};

Chunk::Chunk() :
	m_vao( new opengl::VertexArray() ),
	m_vbo( new opengl::Buffer( opengl::Buffer::Target::ARRAY, opengl::Buffer::Usage::DYNAMIC_DRAW ) ),
	m_uvbo( new opengl::Buffer( opengl::Buffer::Target::ARRAY, opengl::Buffer::Usage::DYNAMIC_DRAW ) )
{
}

void Chunk::populateChunk( unsigned int chunkSize, Vector3 chunkPos )
{
	unsigned int sizeCubed = chunkSize * chunkSize * chunkSize;

	m_chunkSize = chunkSize;
	m_vertsInChunk = sizeCubed * vertInCube;
	m_uvsInChunk = uvInCube * sizeCubed;
	m_chunkPos = chunkPos;

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
}

void Chunk::build()
{
	//    if ( m_populated )
	//        this->clearOpenGL();

	m_chunkVertices = new Vector3[ m_vertsInChunk ];
	Vector2* chunkUVs = new Vector2[ m_uvsInChunk ];

	for (int z = 0; z < m_chunkSize; z++)
	{
		for (int y = 0; y < m_chunkSize; y++)
		{
			for (int x = 0; x < m_chunkSize; x++)
			{
				int memOffset = ( x * vertInCube ) + (m_chunkSize * ((y * vertInCube) + m_chunkSize * (z * vertInCube)));

				std::memcpy( m_chunkVertices + memOffset, CubeVerts, sizeof( CubeVerts ) );
				std::memcpy( chunkUVs + memOffset, CubeUV, sizeof( CubeUV ) );

				for (int face = 0; face < 6; face++)
				{
					int memOffsetOffest = static_cast<int>( face ) * 6;

					for (int q = memOffset + memOffsetOffest; q < memOffset + memOffsetOffest + 6; q++)
					{
						m_chunkVertices[q].x += (x * 2) + (m_chunkPos.x * 2);
						m_chunkVertices[q].y += (y * 2) + (m_chunkPos.y * 2);
						m_chunkVertices[q].z += (z * 2) + (m_chunkPos.z * 2);
					}
				}
			}
		}
	}

	m_vao->bind();

	m_vbo->bind();
	m_vbo->setData( static_cast<void*>(m_chunkVertices), m_vertsInChunk * sizeof(Vector3) );
	opengl::VertexAttrib chunkVertAttribs( 0, 3, opengl::GLType::FLOAT, sizeof(Vector3), 0);
	chunkVertAttribs.enable();

	m_uvbo->bind();
	m_uvbo->setData( static_cast<void*>(chunkUVs), m_uvsInChunk * sizeof(Vector2) );
	opengl::VertexAttrib uvAttribs( 1, 2, opengl::GLType::FLOAT, sizeof(Vector2), 0 );
	uvAttribs.enable();

	m_shader.addStage(opengl::ShaderStage::VERTEX_SHADER, vertexShaderSource);
	m_shader.addStage(opengl::ShaderStage::FRAGMENT_SHADER, fragmentShaderSource);
	m_shader.build();
}

void Chunk::draw(phoenix::FreeRoamCamera& camera)
{
	Matrix4x4 projection = Matrix4x4::perspective(1280.f / 720.f, 45.f, 100.f, 0.1f );

	Matrix4x4 view = camera.calculateViewMatrix();

	Matrix4x4 model;

	m_vao->bind();
	m_shader.use();

	m_shader.setMat4("model", model);
	m_shader.setMat4("view", view);
	m_shader.setMat4("projection", projection);

	m_shader.setInt("theTexture", 0);
	m_shader.setInt("theTexture2", 1);

	glDrawArrays(GL_TRIANGLES, 0, m_vertsInChunk);
}
