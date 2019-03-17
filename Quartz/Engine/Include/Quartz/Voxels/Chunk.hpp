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

#pragma once

#include <Quartz/Core/Math/Math.hpp>
#include <Quartz/Voxels/Block.hpp>
#include <Quartz/Voxels/ChunkRenderer.hpp>
#include <Quartz/Core/Utilities/Threading/SingleWorker.hpp>

#include <vector>

namespace qz
{
	namespace voxels
	{
		enum class BlockFace : int
		{
			FRONT = 0,
			BACK = 1,
			RIGHT = 2,
			LEFT = 3,
			BOTTOM = 4,
			TOP = 5
		};

		struct ChunkMesh
		{
			std::vector<ChunkVert3D> verts;

			gfx::TexCache textureCache;
			std::size_t currentTexLayer = 0;

			void reset();
			std::size_t triangleCount() const;

			ChunkMesh() = default;
		};

		class Chunk
		{
		public:
			Chunk() = delete;
			Chunk(const Chunk& other);
			Chunk& operator=(const Chunk& other);
			Chunk(Chunk&& other) noexcept;
			Chunk& operator=(Chunk&& other) noexcept;

			Chunk(qz::Vector3 chunkPos, int chunkSize, const std::string& defaultBlockID);
			~Chunk() = default;

			void generateTerrain(unsigned int seed);
			void buildMesh();

			const Vector3& getChunkPos() const;

			void breakBlockAt(qz::Vector3 position, const BlockInstance& block);
			void placeBlockAt(qz::Vector3 position, const BlockInstance& block);

			BlockInstance getBlockAt(qz::Vector3 position) const;
			void setBlockAt(qz::Vector3 position, const BlockInstance& newBlock);

			static constexpr int CHUNK_WIDTH = 16;
			static constexpr int CHUNK_HEIGHT = 16;
			static constexpr int CHUNK_DEPTH = 16;

			static std::size_t getVectorIndex(std::size_t x, std::size_t y, std::size_t z)
			{
				return x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z);
			}

			void renderBlocks(int* bufferCounter);

		private:
			Vector3 m_chunkPos;
			bool m_needsMeshing = false;
			bool m_hasBeenMeshed = false;

			std::string m_defaultBlockID;
			std::vector<BlockInstance> m_chunkBlocks;

			ChunkRenderer m_renderer;
			ChunkMesh m_mesh;

			utils::threading::SingleWorker m_worker;

		private:
			void addBlockFace(BlockFace face, qz::Vector3 blockPos, const BlockInstance& block);
		};

	}
}
