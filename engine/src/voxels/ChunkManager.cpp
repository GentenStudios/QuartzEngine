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
		m_managerData->chunks.push_back(Chunk({ 0, 0, 0 }, 16, m_defaultBlock));
	}

	for (int i = 1; i < test + 1; i++)
	{
		m_managerData->chunks.push_back(Chunk({ i * 16.f, 0, 0 }, 16, m_defaultBlock));
	}

	for (auto& chunk : m_managerData->chunks)
	{
		chunk.populateData();
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

