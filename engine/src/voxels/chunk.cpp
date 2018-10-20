#include "engine/common.hpp"

#include "engine/voxels/chunk.hpp"

#include <cstring>

using namespace phoenix;
using namespace phoenix::voxels;

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

const unsigned int VERT_IN_CUBE = 36;
const unsigned int UV_IN_CUBE = 36;

Chunk::Chunk()
{

}

Chunk::~Chunk()
{

}

Block* Chunk::getBlockAt(phoenix::Vector3 position)
{
	return  m_chunkBlocks[position.x][position.y][position.z];
}

void Chunk::setBlockAt(phoenix::Vector3 position, Block block)
{
	m_chunkBlocks[position.x][position.y][position.z] = &block;
}

void Chunk::populateChunk(phoenix::Vector3 chunkSize, phoenix::Vector3 chunkPos, Block defaultBlock)
{
	unsigned int sizeCubed = chunkSize.x * chunkSize.y * chunkSize.z;
	m_vertsInChunk = sizeCubed * VERT_IN_CUBE;
	m_uvsInChunk = UV_IN_CUBE * sizeCubed;

	m_chunkPosition = chunkPos;

	// Set whole array to have, for example, 16 parts inside the vector.
	m_chunkBlocks.resize(static_cast<unsigned int>(m_chunkSize.x));
	for (unsigned int x = 0; x < m_chunkBlocks.size(); x++)
	{
		// Set each X index (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][0] to m_chunkBlocks[x][15]
		m_chunkBlocks[x].resize(static_cast<unsigned int>(m_chunkSize.y));
		for (unsigned int y = 0; y < m_chunkBlocks[x].size(); y++)
		{
			// Set the Y (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][y][0] to m_chunkBlocks[x][y][15]
			m_chunkBlocks[x][y].resize(static_cast<unsigned int>(m_chunkSize.z));
			for (unsigned int z = 0; z < m_chunkBlocks[x][y].size(); z++)
			{
				// Set the Z (first vector part, of the trio) to have the actual value of the blocks data. So, you can have m_chunkBlocks[x][y][z] = BlockType::SOLID
				m_chunkBlocks[x][y][z] = &defaultBlock;
			}
		}
	}
}

void Chunk::build()
{
	m_chunkVertices = new Vector3[m_vertsInChunk];
	m_chunkUVs = new Vector2[m_uvsInChunk];

	for (int z = 0; z < m_chunkSize.x; z++)
	{
		for (int y = 0; y < m_chunkSize.y; y++)
		{
			for (int x = 0; x < m_chunkSize.z; x++)
			{
				int memOffset = (x * VERT_IN_CUBE) + (m_chunkSize.x * ((y * UV_IN_CUBE) + m_chunkSize.y * (z * VERT_IN_CUBE)));

				std::memcpy(m_chunkVertices + memOffset, CubeVerts, sizeof(CubeVerts));
				std::memcpy(m_chunkUVs + memOffset, CubeUV, sizeof(CubeUV));

				for (int face = 0; face < 6; face++)
				{
					int memOffsetOffest = face * 6;

					for (int q = memOffset + memOffsetOffest; q < memOffset + memOffsetOffest + 6; q++)
					{
						m_chunkVertices[q].x += (x * 2) + (m_chunkPosition.x * 2);
						m_chunkVertices[q].y += (y * 2) + (m_chunkPosition.y * 2);
						m_chunkVertices[q].z += (z * 2) + (m_chunkPosition.z * 2);
					}
				}
			}
		}
	}
}
