#include "engine/voxels/Chunk.hpp"
#include <cstring>

using namespace phx::voxels;
using namespace phx;

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

Chunk::Chunk(Vector3 chunkPos, unsigned int chunkSize, Block* defaultBlock)
{
	m_defaultBlock = new Block(*defaultBlock);
	
	m_chunkData = new ChunkData();
	m_chunkData->chunkSize = chunkSize;
	m_chunkData->chunkPos = chunkPos;

	unsigned int sizeCubed = chunkSize * chunkSize * chunkSize;
	m_vertInChunk = sizeCubed * 36;
	m_uvInChunk = sizeCubed * 36;
}

Chunk::~Chunk()
{
	delete m_chunkData;
}

void Chunk::populateData()
{
	// Set whole array to have, for example, 16 elements inside the vector.
	m_chunkData->chunkBlocks.resize(m_chunkData->chunkSize);

	for (unsigned int x = 0; x < m_chunkData->chunkBlocks.size(); x++)
	{
		// Set each X index (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][0] to m_chunkBlocks[x][15]
		m_chunkData->chunkBlocks[x].resize(m_chunkData->chunkSize);
		for (unsigned int y = 0; y < m_chunkData->chunkBlocks.size(); y++)
		{
			// Set the Y (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][y][0] to m_chunkBlocks[x][y][15]
			m_chunkData->chunkBlocks[x][y].resize(m_chunkData->chunkSize);
			for (unsigned int z = 0; z < m_chunkData->chunkBlocks.size(); z++)
			{
				// Set the Z (first vector part, of the trio) to have the actual value of the blocks data. So, you can have m_chunkBlocks[x][y][z] = BlockType::SOLID
				if (z % 4 != 0)
					m_chunkData->chunkBlocks[x][y][z] = m_defaultBlock;
				else
					m_chunkData->chunkBlocks[x][y][z] = new Block(BlockLibrary::getBlockByID("core:air"));
			}
		}
	}

	m_chunkData->chunkVertices.resize(m_vertInChunk);
	m_chunkData->chunkUVs.resize(m_uvInChunk);

	for (unsigned int z = 0; z < m_chunkData->chunkSize; z++)
	{
		for (unsigned int y = 0; y < m_chunkData->chunkSize; y++)
		{
			for (unsigned int x = 0; x < m_chunkData->chunkSize; x++)
			{
				if (m_chunkData->chunkBlocks[x][y][z]->getID() == "core:air")
					continue;

				int memOffset = (x * 36) + (m_chunkData->chunkSize * ((y * 36) + m_chunkData->chunkSize * (z * 36)));

				std::memcpy(m_chunkData->chunkVertices.data() + memOffset, CubeVerts, sizeof(CubeVerts));
				std::memcpy(m_chunkData->chunkUVs.data() + memOffset, CubeUV, sizeof(CubeUV));

				if (x == 0 || m_chunkData->chunkBlocks[x - 1][y][z]->getID() == "core:air")
					addFace(BlockFace::Right, memOffset, x, y, z);
				if (x == m_chunkData->chunkSize - 1 || m_chunkData->chunkBlocks[x + 1][y][z]->getID() == "core:air")
					addFace(BlockFace::Left, memOffset, x, y, z);
				
				if (y == 0 || m_chunkData->chunkBlocks[x][y - 1][z]->getID() == "core:air")
					addFace(BlockFace::Bottom, memOffset, x, y, z);
				if (y == m_chunkData->chunkSize - 1 || m_chunkData->chunkBlocks[x][y + 1][z]->getID() == "core:air")
					addFace(BlockFace::Top, memOffset, x, y, z);
				
				if (z == 0 || m_chunkData->chunkBlocks[x][y][z - 1]->getID() == "core:air")
					addFace(BlockFace::Front, memOffset, x, y, z);
				if (z == m_chunkData->chunkSize - 1 || m_chunkData->chunkBlocks[x][y][z + 1]->getID() == "core:air")
					addFace(BlockFace::Left, memOffset, x, y, z);
			}
		}
	}
}

void Chunk::addFace(BlockFace face, int memOffset, int x, int y, int z)
{
	int memOffsetOffest = static_cast<int>(face) * 6;

	for (int q = memOffset + memOffsetOffest; q < memOffset + memOffsetOffest + 6; q++)
	{
		m_chunkData->chunkVertices[q].x += (x * 2) + (m_chunkData->chunkPos.x * 2);
		m_chunkData->chunkVertices[q].y += (y * 2) + (m_chunkData->chunkPos.y * 2);
		m_chunkData->chunkVertices[q].z += (z * 2) + (m_chunkData->chunkPos.z * 2);
	}
}
