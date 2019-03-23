// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#include <Quartz/Core/QuartzPCH.hpp>
#include <Quartz/Voxels/ChunkManager.hpp>
#include <Quartz/Voxels/Terrain/PerlinNoise.hpp>

#include <algorithm>

using namespace qz::voxels;
using namespace qz;

const int VIEW_DISTANCE = 16; // 96 blocks, 6 chunks.

ChunkManager::ChunkManager(const std::string& blockID, unsigned int seed) :
	m_seed(seed), m_defaultBlockID(blockID)
{}

void ChunkManager::toggleWireframe()
{
	m_wireframe = !m_wireframe;
	glPolygonMode(GL_FRONT_AND_BACK, m_wireframe ? GL_LINE : GL_FILL);
}

bool ChunkManager::isWireframe() const
{
	return m_wireframe;
}

void ChunkManager::determineGeneration(qz::Vector3 cameraPosition)
{
	cameraPosition = cameraPosition / 2.f;
	cameraPosition += 0.5f;

	const int posX = static_cast<int>(cameraPosition.x) / Chunk::CHUNK_WIDTH;
	const int posY = static_cast<int>(cameraPosition.y) / Chunk::CHUNK_HEIGHT;
	const int posZ = static_cast<int>(cameraPosition.z) / Chunk::CHUNK_DEPTH;

	// Get diameter to generate for.
	const int chunkViewDistanceX = VIEW_DISTANCE / Chunk::CHUNK_WIDTH;
	const int chunkViewDistanceY = VIEW_DISTANCE / Chunk::CHUNK_HEIGHT;
	const int chunkViewDistanceZ = VIEW_DISTANCE / Chunk::CHUNK_DEPTH;

	for (int x = -chunkViewDistanceX; x <= chunkViewDistanceX; x++)
	{
		for (int y = -chunkViewDistanceY; y <= chunkViewDistanceY; y++)
		{
			for (int z = -chunkViewDistanceZ; z <= chunkViewDistanceZ; z++)
			{
				qz::Vector3 chunkToCheck = {
					static_cast<float>(x) * chunkViewDistanceX + posX,
					static_cast<float>(y) * chunkViewDistanceY + posY,
					static_cast<float>(z) * chunkViewDistanceZ + posZ
				};

				chunkToCheck.x *= Chunk::CHUNK_WIDTH;
				chunkToCheck.y *= Chunk::CHUNK_HEIGHT;
				chunkToCheck.z *= Chunk::CHUNK_DEPTH;

				auto result = std::find_if(m_chunks.begin(), m_chunks.end(),
					[chunkToCheck](const Chunk& o) -> bool
					{
						return o.getChunkPos() == chunkToCheck;
					});

				if (result == m_chunks.end())
				{
					m_chunks.emplace_back(chunkToCheck, m_defaultBlockID);
					m_chunks.back().generateTerrain(m_seed);
				}
			}
		}
	}
}

void ChunkManager::testGeneration()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			qz::Vector3 pain = { i * 16.f, 0.f, j * 16.f };

			m_chunks.emplace_back(pain, m_defaultBlockID);
			m_chunks.back().generateTerrain(m_seed);
		}

	}
}

void ChunkManager::unloadRedundant()
{
	// TODO this.
}

void ChunkManager::setBlockAt(qz::Vector3 position, const BlockInstance& block)
{
	int posX = static_cast<int>(position.x / Chunk::CHUNK_WIDTH);
	int posY = static_cast<int>(position.y / Chunk::CHUNK_HEIGHT);
	int posZ = static_cast<int>(position.z / Chunk::CHUNK_DEPTH);

	position.x = static_cast<float>(static_cast<int>(position.x) % Chunk::CHUNK_WIDTH);
	if (position.x < 0)
	{
		posX -= 1;
		position.x += Chunk::CHUNK_WIDTH;
	}

	position.y = static_cast<float>(static_cast<int>(position.y) % Chunk::CHUNK_HEIGHT);
	if (position.y < 0)
	{
		posY -= 1;
		position.y += Chunk::CHUNK_HEIGHT;
	}

	position.z = static_cast<float>(static_cast<int>(position.z) % Chunk::CHUNK_DEPTH);
	if (position.z < 0)
	{
		posZ -= 1;
		position.z += Chunk::CHUNK_DEPTH;
	}

	const qz::Vector3 chunkPosition = {
		static_cast<float>(posX * Chunk::CHUNK_WIDTH),
		static_cast<float>(posY * Chunk::CHUNK_HEIGHT),
		static_cast<float>(posZ * Chunk::CHUNK_DEPTH)
	};

	for (auto& chunk : m_chunks)
	{
		if (chunk.getChunkPos() == chunkPosition)
		{
			chunk.setBlockAt(
				{ // "INLINE" VECTOR 3 DECLARATION
				position.x, // x position IN the chunk, not overall 
				position.y, // y position IN the chunk, not overall 
				position.z  // z position IN the chunk, not overall 
				},
				block
			);

			break;
		}
	}
}

BlockInstance ChunkManager::getBlockAt(qz::Vector3 position) const
{
	int posX = static_cast<int>(position.x / Chunk::CHUNK_WIDTH);
	int posY = static_cast<int>(position.y / Chunk::CHUNK_HEIGHT);
	int posZ = static_cast<int>(position.z / Chunk::CHUNK_DEPTH);

	position.x = static_cast<float>(static_cast<int>(position.x) % Chunk::CHUNK_WIDTH);
	if (position.x < 0)
	{
		posX -= 1;
		position.x += Chunk::CHUNK_WIDTH;
	}

	position.y = static_cast<float>(static_cast<int>(position.y) % Chunk::CHUNK_HEIGHT);
	if (position.y < 0)
	{
		posY -= 1;
		position.y += Chunk::CHUNK_HEIGHT;
	}

	position.z = static_cast<float>(static_cast<int>(position.z) % Chunk::CHUNK_DEPTH);
	if (position.z < 0)
	{
		posZ -= 1;
		position.z += Chunk::CHUNK_DEPTH;
	}

	const qz::Vector3 chunkPosition = {
		static_cast<float>(posX * Chunk::CHUNK_WIDTH),
		static_cast<float>(posY * Chunk::CHUNK_HEIGHT),
		static_cast<float>(posZ * Chunk::CHUNK_DEPTH)
	};

	for (auto& chunk : m_chunks)
	{
		if (chunk.getChunkPos() == chunkPosition)
		{
			return chunk.getBlockAt(
				{ // "INLINE" VECTOR 3 DECLARATION
				position.x, // x position IN the chunk, not overall 
				position.y, // y position IN the chunk, not overall 
				position.z  // z position IN the chunk, not overall 
				}
			);
		}
	}

	return BlockInstance("core:out_of_bounds");
}

void ChunkManager::breakBlockAt(qz::Vector3 position, const BlockInstance& block)
{
	int posX = static_cast<int>(position.x / Chunk::CHUNK_WIDTH);
	int posY = static_cast<int>(position.y / Chunk::CHUNK_HEIGHT);
	int posZ = static_cast<int>(position.z / Chunk::CHUNK_DEPTH);

	position.x = static_cast<float>(static_cast<int>(position.x) % Chunk::CHUNK_WIDTH);
	if (position.x < 0)
	{
		posX -= 1;
		position.x += Chunk::CHUNK_WIDTH;
	}

	position.y = static_cast<float>(static_cast<int>(position.y) % Chunk::CHUNK_HEIGHT);
	if (position.y < 0)
	{
		posY -= 1;
		position.y += Chunk::CHUNK_HEIGHT;
	}

	position.z = static_cast<float>(static_cast<int>(position.z) % Chunk::CHUNK_DEPTH);
	if (position.z < 0)
	{
		posZ -= 1;
		position.z += Chunk::CHUNK_DEPTH;
	}

	const qz::Vector3 chunkPosition = {
		static_cast<float>(posX * Chunk::CHUNK_WIDTH),
		static_cast<float>(posY * Chunk::CHUNK_HEIGHT),
		static_cast<float>(posZ * Chunk::CHUNK_DEPTH)
	};

	for (auto& chunk : m_chunks)
	{
		if (chunk.getChunkPos() == chunkPosition)
		{
			chunk.breakBlockAt(
				{ // "INLINE" VECTOR 3 DECLARATION
				position.x, // x position IN the chunk, not overall 
				position.y, // y position IN the chunk, not overall 
				position.z  // z position IN the chunk, not overall 
				},
				block
			);

			break;
		}
	}
}

void ChunkManager::placeBlockAt(qz::Vector3 position, const BlockInstance& block)
{
	int posX = static_cast<int>(position.x / Chunk::CHUNK_WIDTH);
	int posY = static_cast<int>(position.y / Chunk::CHUNK_HEIGHT);
	int posZ = static_cast<int>(position.z / Chunk::CHUNK_DEPTH);

	position.x = static_cast<float>(static_cast<int>(position.x) % Chunk::CHUNK_WIDTH);
	if (position.x < 0)
	{
		posX -= 1;
		position.x += Chunk::CHUNK_WIDTH;
	}

	position.y = static_cast<float>(static_cast<int>(position.y) % Chunk::CHUNK_HEIGHT);
	if (position.y < 0)
	{
		posY -= 1;
		position.y += Chunk::CHUNK_HEIGHT;
	}

	position.z = static_cast<float>(static_cast<int>(position.z) % Chunk::CHUNK_DEPTH);
	if (position.z < 0)
	{
		posZ -= 1;
		position.z += Chunk::CHUNK_DEPTH;
	}

	const qz::Vector3 chunkPosition = {
		static_cast<float>(posX * Chunk::CHUNK_WIDTH),
		static_cast<float>(posY * Chunk::CHUNK_HEIGHT),
		static_cast<float>(posZ * Chunk::CHUNK_DEPTH)
	};

	for (auto& chunk : m_chunks)
	{
		if (chunk.getChunkPos() == chunkPosition)
		{
			chunk.placeBlockAt(
				{ // "INLINE" VECTOR 3 DECLARATION
				position.x, // x position IN the chunk, not overall 
				position.y, // y position IN the chunk, not overall 
				position.z  // z position IN the chunk, not overall 
				},
				block
			);

			break;
		}
	}
}

void ChunkManager::render(const int bufferCounter)
{
	int count1 = bufferCounter;

	for (Chunk& chunk : m_chunks)
	{
		chunk.renderBlocks(&count1);
	}
}
