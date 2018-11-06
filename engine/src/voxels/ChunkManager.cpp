#include "engine/voxels/ChunkManager.hpp"

using namespace phx::voxels;

ChunkManager::ChunkManager()
{
	m_managerData = new ChunkContainer();
}

ChunkManager::~ChunkManager()
{}

void ChunkManager::setDefaultBlock(Block* block)
{
	m_defaultBlock = block;
}

void ChunkManager::testGeneration(int test)
{
	if (m_managerData->chunks.size() == 0)
	{
		Vector3 position = { 0, 0, 0 };
		m_managerData->chunks.push_back(Chunk(position, 16, m_defaultBlock));
		m_managerData->positions.push_back(position);
	}

	for (int i = 1; i < test + 1; i++)
	{
		Vector3 position = { i * 16.f, 0, 0 };
		m_managerData->chunks.push_back(Chunk({position.x, position.y, position.z}, 16, m_defaultBlock));
		m_managerData->positions.push_back(position);
	}

	for (auto& chunk : m_managerData->chunks)
	{
		chunk.populateData();
	}
}

void ChunkManager::setBlockAt(phx::Vector3 position, Block* block)
{
	int pos_x = (position.x / 16);
	int pos_y = (position.y / 16);
	int pos_z = (position.z / 16);

		for (auto& chunk : m_managerData->chunks)
	{
		if (chunk.getChunkPos() == phx::Vector3(pos_x * 16.f, pos_y * 16.f, pos_z * 16.f))
		{
			chunk.setBlockAt(
				{ // "INLINE" VECTOR 3 DECLARATION
				static_cast<float>(static_cast<int>(position.x) % 16), // x position IN the chunk, not overall 
				static_cast<float>(static_cast<int>(position.y) % 16), // y position IN the chunk, not overall 
				static_cast<float>(static_cast<int>(position.z) % 16)  // z position IN the chunk, not overall 
				}, 
				block
			);

			break;
		}
	}
}

void ChunkManager::render(int bufferCounter)
{
	int count1 = bufferCounter;

	for (auto& chunk : m_managerData->chunks)
	{
		chunk.render(&count1);
	}
}