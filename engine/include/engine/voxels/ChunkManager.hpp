#pragma once

#include "engine/common.hpp"

#include "engine/voxels/Block.hpp"
#include "engine/voxels/Chunk.hpp"

namespace phx
{
	namespace voxels
	{
		struct ChunkContainer
		{
			std::vector<Chunk> chunks;
			std::vector<Vector3> positions;
		};

		class ChunkManager
		{
		public:
			ChunkManager();
			~ChunkManager();

			void setDefaultBlock(Block* block);

			void determineGeneration(int test);
			void testGeneration(int test);
			void unloadRedundant() { /* TODO this. */ }
						
			void render(int bufferCounter);

		private:
			ChunkContainer* m_managerData;
			Block* m_defaultBlock;
		};

	}
}