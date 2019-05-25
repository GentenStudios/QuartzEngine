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
#include <Quartz/Core/Utilities/Logger.hpp>
#include <Quartz/Graphics/RHI/BufferLayout.hpp>
#include <Quartz/Voxels/Chunk.hpp>
#include <Quartz/Voxels/ChunkBlockVerts.hpp>
#include <Quartz/Voxels/Terrain/PerlinNoise.hpp>

using namespace qz::voxels;
using namespace qz;

void ChunkMesh::reset()
{
	verts.clear();
	verts.shrink_to_fit();
}

std::size_t ChunkMesh::triangleCount() const
{
	return verts.size() / 3;
}

Chunk::Chunk(const Chunk& other) : m_needsMeshing(false)
{
	m_chunkPos = other.m_chunkPos;
	m_defaultBlockID = other.m_defaultBlockID;
	m_chunkBlocks = other.m_chunkBlocks;
	m_needsMeshing = other.m_needsMeshing;
}

Chunk& Chunk::operator=(const Chunk& other)
{
	if (&other == this)
		return *this;

	m_chunkPos = other.m_chunkPos;
	m_defaultBlockID = other.m_defaultBlockID;
	m_chunkBlocks = other.m_chunkBlocks;
	m_needsMeshing = other.m_needsMeshing;

	return *this;
}

Chunk::Chunk(Chunk&& other) noexcept
{
	m_chunkPos = other.m_chunkPos;
	m_defaultBlockID = std::move(other.m_defaultBlockID);
	m_chunkBlocks = std::move(other.m_chunkBlocks);
	m_needsMeshing = other.m_needsMeshing;
}

Chunk& Chunk::operator=(Chunk&& other) noexcept
{
	m_chunkPos = other.m_chunkPos;
	m_defaultBlockID = std::move(other.m_defaultBlockID);
	m_chunkBlocks = std::move(other.m_chunkBlocks);
	m_needsMeshing = other.m_needsMeshing;

	return *this;
}

Chunk::Chunk(qz::Vector3 chunkPos, const std::string& defaultBlockID)
{
	m_chunkPos = chunkPos;
	m_defaultBlockID = defaultBlockID;

	for (int i = 0; i < CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH; ++i)
		m_chunkBlocks.emplace_back(m_defaultBlockID);
}

void Chunk::generateTerrain(unsigned int seed)
{
	PerlinNoise* terrainGenerator = new PerlinNoise(seed);
	terrainGenerator->generateFor(m_chunkBlocks, m_chunkPos);
	delete terrainGenerator;

	m_needsMeshing = true;
}

void Chunk::buildMesh()
{
	std::vector<BlockInstance> blocks = m_chunkBlocks;
	m_mesh.reset();

	for (int j = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH; j > 0; --j)
	{
		int i = j - 1;
		BlockInstance& block = blocks[i];

		if (block.getBlockType() == BlockType::GAS)
			continue;

		const int x = i % CHUNK_WIDTH;
		const int y = (i / CHUNK_WIDTH) % CHUNK_HEIGHT;
		const int z = i / (CHUNK_WIDTH * CHUNK_HEIGHT);

		if (x == 0 || m_chunkBlocks[getVectorIndex(x - 1, y, z)].getBlockType() != BlockType::SOLID)
			addBlockFace(BlockFace::RIGHT, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, block);
		if (x == CHUNK_WIDTH - 1 || m_chunkBlocks[getVectorIndex(x + 1, y, z)].getBlockType() != BlockType::SOLID)
			addBlockFace(BlockFace::LEFT, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, block);

		if (y == 0 || m_chunkBlocks[getVectorIndex(x, y - 1, z)].getBlockType() != BlockType::SOLID)
			addBlockFace(BlockFace::BOTTOM, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, block);
		if (y == CHUNK_HEIGHT - 1 || m_chunkBlocks[getVectorIndex(x, y + 1, z)].getBlockType() != BlockType::SOLID)
			addBlockFace(BlockFace::TOP, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, block);

		if (z == 0 || m_chunkBlocks[getVectorIndex(x, y, z - 1)].getBlockType() != BlockType::SOLID)
			addBlockFace(BlockFace::FRONT, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, block);
		if (z == CHUNK_DEPTH - 1 || m_chunkBlocks[getVectorIndex(x, y, z + 1)].getBlockType() != BlockType::SOLID)
			addBlockFace(BlockFace::BACK, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, block);
	}

	m_hasBeenMeshed = true;
}

const Vector3& Chunk::getChunkPos() const
{
	return m_chunkPos;
}

void Chunk::breakBlockAt(qz::Vector3 position, const BlockInstance& block)
{
	if (position.x < CHUNK_WIDTH)
	{
		if (position.y < CHUNK_HEIGHT)
		{
			if (position.z < CHUNK_DEPTH)
			{
				BlockInstance& orig = m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))];

				auto& breakCallback = BlockLibrary::get()->requestBlock(orig.getBlockID()).getBreakCallback();
				if (breakCallback != nullptr)
					breakCallback();

				orig = block;

				m_needsMeshing = true;
			}
		}
	}
}

void Chunk::placeBlockAt(qz::Vector3 position, const BlockInstance& block)
{
	if (position.x < CHUNK_WIDTH)
	{
		if (position.y < CHUNK_HEIGHT)
		{
			if (position.z < CHUNK_DEPTH)
			{
				auto& placeCallback = BlockLibrary::get()->requestBlock(block.getBlockID()).getPlaceCallback();
				if (placeCallback != nullptr)
					placeCallback();

				m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))] = block;

				m_needsMeshing = true;
			}
		}
	}
}

BlockInstance Chunk::getBlockAt(qz::Vector3 position) const
{
	if (position.x < CHUNK_WIDTH)
	{
		if (position.y < CHUNK_HEIGHT)
		{
			if (position.z < CHUNK_DEPTH)
			{
				return m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))];
			}
		}
	}

	return BlockInstance("core:out_of_bounds");
}

void Chunk::setBlockAt(qz::Vector3 position, const BlockInstance& newBlock)
{
	if (position.x < CHUNK_WIDTH)
	{
		if (position.y < CHUNK_HEIGHT)
		{
			if (position.z < CHUNK_DEPTH)
			{
				m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))] = newBlock;

				m_needsMeshing = true;
			}
		}
	}
}

void Chunk::renderBlocks(int* bufferCounter)
{
	if (m_hasBeenMeshed)
	{
		if (m_renderer.updateMesh(m_mesh, bufferCounter))
			m_hasBeenMeshed = false;
	}

	m_renderer.render();

	if (m_needsMeshing)
	{
		m_worker.addWork(std::bind(&Chunk::buildMesh, this));
		m_needsMeshing = false;
	}
}

void Chunk::addBlockFace(BlockFace face, qz::Vector3 blockPos, const BlockInstance& block)
{
	if (block.getBlockType() == BlockType::SOLID)
	{
		int texLayer = -1;

		auto& blockTexList = block.getBlockTextures();

		if (static_cast<std::size_t>(face) < blockTexList.size())
		{
			auto it = m_mesh.textureCache.find(blockTexList[static_cast<int>(face)]);
			if (it == m_mesh.textureCache.end())
			{
				m_mesh.textureCache.emplace(blockTexList[static_cast<int>(face)], m_mesh.currentTexLayer);
				texLayer = m_mesh.currentTexLayer;
				++m_mesh.currentTexLayer;
			}
			else
			{
				texLayer = it->second;
			}
		}

		for (int i = 0; i < NUM_VERTS_IN_FACE; ++i)
		{
			qz::Vector3 blockVertices = CUBE_VERTS[(static_cast<int>(face) * NUM_FACES_IN_CUBE) + i];
			blockVertices.x += (blockPos.x * ACTUAL_CUBE_SIZE) + (m_chunkPos.x * ACTUAL_CUBE_SIZE); // Multiply by 2, as that is the size of the actual cube edges, indicated by the cube vertices.
			blockVertices.y += (blockPos.y * ACTUAL_CUBE_SIZE) + (m_chunkPos.y * ACTUAL_CUBE_SIZE);
			blockVertices.z += (blockPos.z * ACTUAL_CUBE_SIZE) + (m_chunkPos.z * ACTUAL_CUBE_SIZE);

			qz::Vector2 cubeUVs = CUBE_UV[(static_cast<int>(face) * NUM_FACES_IN_CUBE) + i];

			m_mesh.verts.emplace_back(blockVertices, cubeUVs, texLayer);
		}
	}
}
