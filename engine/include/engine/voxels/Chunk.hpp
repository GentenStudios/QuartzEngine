#pragma once

#include "engine/common.hpp"
#include "engine/math/Vector3.hpp"
#include "engine/math/Vector2.hpp"

#include "engine/voxels/Block.hpp"

#include "engine/graphics/opengl/VertexBuffer.hpp"
#include "engine/graphics/opengl/VertexAttrib.hpp"

namespace phx
{
	namespace voxels
	{

		struct ChunkData
		{
			// Data to allow for identifying where this chunk's data is.
			phx::Vector3 chunkPos;
			unsigned int chunkSize;

			std::vector<std::vector<std::vector<Block*>>> chunkBlocks;
			std::vector<phx::Vector3> chunkVertices;
			std::vector<phx::Vector3> chunkNormals;
			std::vector<phx::Vector2> chunkUVs;
			std::vector<int> chunkTexLayers;
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

		class Chunk
		{
		public:
			Chunk(phx::Vector3 chunkPos, unsigned int chunkSize, Block* defaultBlock);
			~Chunk();

			void populateData();

			void buildMesh();

			void breakBlockAt(phx::Vector3 position, Block* replaceBlock);
			void placeBlockAt(phx::Vector3 position);

			Block getBlockAt(phx::Vector3 position);
			void setBlockAt(phx::Vector3 position, Block& block);

			ChunkData* getChunkDataPointer() { return m_chunkData; }
			ChunkData* m_chunkData;

		private:
			Block* m_defaultBlock;

			unsigned int m_vertInChunk;
			unsigned int m_normalInChunk;
			unsigned int m_uvInChunk;

			void addFace(BlockFace face, int memOffset, int x, int y, int z);
		};

	}
}