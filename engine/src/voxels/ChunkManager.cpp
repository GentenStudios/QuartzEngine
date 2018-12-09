#include <engine/voxels/ChunkManager.hpp>

using namespace phx::voxels;

ChunkManager::ChunkManager(const std::string& blockID) : 
	m_wireframe(false), 
	m_defaultBlockID(blockID)
{
	m_managerData = new ChunkContainer();
}

ChunkManager::~ChunkManager()
{}

void ChunkManager::toggleWireframe()
{
	m_wireframe = !m_wireframe;
	glPolygonMode(GL_FRONT_AND_BACK, m_wireframe ? GL_LINE : GL_FILL);
}

void ChunkManager::testGeneration(int test)
{
#pragma omp parallel
	for (unsigned int z = 0; z < test; z++)
	{
		for (unsigned int y = 0; y < test; y++)
		{
			for (unsigned int x = 0; x < test; x++)
			{
				if (sqrt(static_cast<float>((x - test / 2) * (x - test / 2) + (y - test / 2) * (y - test / 2) + (z - test / 2) * (z - test / 2))) < test / 2)
				{
					int pos_x = (x / 16);
					int pos_y = (y / 16);
					int pos_z = (z / 16);

					phx::Vector3 temp = phx::Vector3(pos_x * 16.f, pos_y * 16.f, pos_z * 16.f);

					bool found = false;

					for (auto& chunk : m_managerData->chunks)
					{
						if (chunk.getChunkPos() == temp)
						{
							chunk.setBlockAt(
								{ // "INLINE" VECTOR 3 DECLARATION
								static_cast<float>(static_cast<int>(x) % 16), // x position IN the chunk, not overall 
								static_cast<float>(static_cast<int>(y) % 16), // y position IN the chunk, not overall 
								static_cast<float>(static_cast<int>(z) % 16)  // z position IN the chunk, not overall 
								},
								BlockInstance("core:grass")
							);

							found = true;

							break;
						}
					}

					if (found == false)
					{
						m_managerData->chunks.push_back(Chunk(temp, 16, m_defaultBlockID));

						for (auto& chunk : m_managerData->chunks)
						{
							if (chunk.getChunkPos() == temp)
							{
								chunk.populateData();

								chunk.setBlockAt(
									{ // "INLINE" VECTOR 3 DECLARATION
									static_cast<float>(static_cast<int>(x) % 16), // x position IN the chunk, not overall 
									static_cast<float>(static_cast<int>(y) % 16), // y position IN the chunk, not overall 
									static_cast<float>(static_cast<int>(z) % 16)  // z position IN the chunk, not overall 
									},
									BlockInstance("core:grass")
								);

								found = true;

								break;
							}
						}

					}
				}
			}
		}
	}

}

void ChunkManager::setBlockAt(phx::Vector3 position, const BlockInstance& block)
{
	int pos_x = (position.x / 16);
	int pos_y = (position.y / 16);
	int pos_z = (position.z / 16);

	phx::Vector3 temp = phx::Vector3(pos_x * 16.f, pos_y * 16.f, pos_z * 16.f);

	for (auto& chunk : m_managerData->chunks)
	{
		if (chunk.getChunkPos() == temp)
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

BlockInstance ChunkManager::getBlockAt(phx::Vector3 position)
{
	int pos_x = (position.x / 16);
	int pos_y = (position.y / 16);
	int pos_z = (position.z / 16);

	phx::Vector3 temp = phx::Vector3(pos_x * 16.f, pos_y * 16.f, pos_z * 16.f);

	for (auto& chunk : m_managerData->chunks)
	{
		if (chunk.getChunkPos() == temp)
		{
			return chunk.getBlockAt(
				{ // "INLINE" VECTOR 3 DECLARATION
				static_cast<float>(static_cast<int>(position.x) % 16), // x position IN the chunk, not overall 
				static_cast<float>(static_cast<int>(position.y) % 16), // y position IN the chunk, not overall 
				static_cast<float>(static_cast<int>(position.z) % 16)  // z position IN the chunk, not overall 
				}
			);

			break;
		}
	}

	return BlockInstance("core:out_of_bounds");
}

void ChunkManager::breakBlockAt(phx::Vector3 position, const BlockInstance& block)
{
	int pos_x = (position.x / 16);
	int pos_y = (position.y / 16);
	int pos_z = (position.z / 16);

	phx::Vector3 temp = phx::Vector3(pos_x * 16.f, pos_y * 16.f, pos_z * 16.f);

	for (auto& chunk : m_managerData->chunks)
	{
		if (chunk.getChunkPos() == temp)
		{
			chunk.breakBlockAt(
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

void ChunkManager::placeBlockAt(phx::Vector3 position, const BlockInstance& block)
{
	int pos_x = (position.x / 16);
	int pos_y = (position.y / 16);
	int pos_z = (position.z / 16);

	phx::Vector3 temp = phx::Vector3(pos_x * 16.f, pos_y * 16.f, pos_z * 16.f);

	for (auto& chunk : m_managerData->chunks)
	{
		if (chunk.getChunkPos() == temp)
		{
			chunk.placeBlockAt(
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