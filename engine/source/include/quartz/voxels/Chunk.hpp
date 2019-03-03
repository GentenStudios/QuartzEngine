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

#include <vector>
#include <mutex>

#include <quartz/core/math/Math.hpp>

#include <quartz/voxels/Block.hpp>

#include <quartz/core/graphics/API/IStateManager.hpp>
#include <quartz/core/graphics/API/IBuffer.hpp>
#include <quartz/core/graphics/API/ITextureArray.hpp>

#include <atomic>

namespace qz
{
	namespace voxels
	{
		enum ChunkFlags : unsigned int
		{
			BLOCKS_NEED_BUFFERING	= 1 << 0,
			OBJECTS_NEED_BUFFERING	= 1 << 1,
			WATER_NEEDS_BUFFERING	= 1 << 2,
			NEEDS_MESHING			= 1 << 3,
			BLOCKS_NEED_TEXTURING	= 1 << 4,
			OBJECTS_NEED_TEXTURING	= 1 << 5,
		};

		enum class BlockFace : int
		{
			FRONT = 0,
			BACK = 1,
			RIGHT = 2,
			LEFT = 3,
			BOTTOM = 4,
			TOP = 5
		};

		struct Mesh
		{
			std::vector<qz::Vector3> vertices;
			std::vector<qz::Vector3> normals;
			std::vector<qz::Vector2> uvs;
			std::vector<int> texLayers;

			void reset();
			void update(const Mesh& other);

			std::size_t triangleCount() const;
		};

		class Chunk;

		class ChunkMesh
		{
		public:
			ChunkMesh() = default;
			~ChunkMesh() = default;

			ChunkMesh(const ChunkMesh& other);
			ChunkMesh& operator=(const ChunkMesh& other);
			
			ChunkMesh(ChunkMesh&& other);
			ChunkMesh& operator=(ChunkMesh&& other);

			void add(const BlockInstance& block, BlockFace face, qz::Vector3 chunkPos, qz::Vector3 blockPos, Chunk* chunk);

			const Mesh& getBlockMesh() const;
			const Mesh& getObjectMesh() const;
			const Mesh& getWaterMesh() const;

			void resetAll();

		private:
			Mesh m_blockMesh;
			Mesh m_objectMesh;
			Mesh m_waterMesh;
		};

		class ChunkRenderer
		{
		public:
			ChunkRenderer();
			~ChunkRenderer();

			ChunkRenderer(const ChunkRenderer& other);
			ChunkRenderer& operator=(const ChunkRenderer& other);

			ChunkRenderer(ChunkRenderer&& other);
			ChunkRenderer& operator=(ChunkRenderer&& other);

			void resetMesh();
			void updateMesh(const Mesh& mesh);

			void reserveTexture(const std::string& path);
			int getTexLayer(const std::string& path);

			void loadTextures();

			void bufferData();
			void render() const;

			std::size_t getTrianglesCount() const;

		private:
			Mesh m_mesh;

			gfx::api::GraphicsResource<gfx::api::IStateManager> m_stateManager = nullptr;
			gfx::api::GraphicsResource<gfx::api::IBuffer> m_buffer = nullptr;

			gfx::api::GraphicsResource<gfx::api::ITextureArray> m_textureArray = nullptr;
			gfx::TexCache m_texReservations;

			int m_currentLayer = 0;
		};

		class Chunk
		{
		public:
			Chunk() = delete;
			
			Chunk(const Chunk& other);
			Chunk& operator=(const Chunk& other);

			Chunk(Chunk&& other);
			Chunk& operator=(Chunk&& other);

			Chunk(qz::Vector3 chunkPos, int chunkSize, const std::string& defaultBlockID);

			~Chunk() = default;

			void populateData(unsigned int seed);

			void buildMesh();

			const ChunkMesh& getChunkMesh() const;
			const Vector3& getChunkPos() const;

			void breakBlockAt(qz::Vector3 position, const BlockInstance& block);
			void placeBlockAt(qz::Vector3 position, const BlockInstance& block);

			BlockInstance getBlockAt(qz::Vector3 position) const;
			void setBlockAt(qz::Vector3 position, const BlockInstance& newBlock);

			ChunkRenderer& getBlockRenderer();
			ChunkRenderer& getObjectRenderer();
			ChunkRenderer& getWaterRenderer();

			void renderBlocks(int* counter);
			void renderObjects(int* counter);
			void renderWater(int* counter);

		private:
			Vector3 m_chunkPos;
			int m_chunkSize;

			ChunkMesh m_mesh;

			ChunkRenderer m_blockRenderer;
			ChunkRenderer m_objectRenderer;
			ChunkRenderer m_waterRenderer;

			unsigned int m_chunkFlags;

			std::string m_defaultBlockID;
			std::vector<BlockInstance> m_chunkBlocks;

			std::size_t getVectorIndex(std::size_t x, std::size_t y, std::size_t z) const
			{
				return x + m_chunkSize * (y + m_chunkSize * z);
			}
		};

	}
}
