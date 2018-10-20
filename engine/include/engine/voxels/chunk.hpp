#pragma once

#include "engine/common.hpp"

#include "engine/math/vector3.hpp"
#include "engine/math/vector2.hpp"
#include "engine/voxels/block.hpp"

namespace phoenix {
	namespace voxels {

		class Chunk
		{
		public:
			Chunk();
			~Chunk();

			/**
			 * @brief Gets the block at the specified position.
			 * @param x The X coordinate
			 * @param y The Y Coordinate
			 * @param z The Z Coordinate
			 * @return Returns a "Block" object
			 */
			Block* getBlockAt(phoenix::Vector3 position);

			/**
			 * @brief setBlockAt
			 * @param x
			 * @param y
			 * @param z
			 * @param block
			 */
			void setBlockAt(phoenix::Vector3 position, Block block);

			/**
			 * @brief Populates Chunk with empty vertices, while resizing the vector.
			 * @param size
			 * @param chunkPos
			 */
			void populateChunk(phoenix::Vector3 chunkSize, phoenix::Vector3 chunkPos, Block defaultBlock);

			/// @brief Builds the Chunk with meshing.
			void build();

		private:
			/// 3 Dimensional Vector. Slightly funkier than a 3D array, but more flexible
			/// or maybe not, I don't know.
			std::vector< std::vector< std::vector< Block* > > > m_chunkBlocks;

			phoenix::Vector3 m_chunkPosition;
			phoenix::Vector3 m_chunkSize;

			int m_vertsInChunk, m_uvsInChunk;
			phoenix::Vector3* m_chunkVertices;
			phoenix::Vector2* m_chunkUVs;
		};
	}
}
