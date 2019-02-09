#pragma once

#include <quartz/core/utils/ThreadPool.hpp>

#include <quartz/voxels/Block.hpp>
#include <quartz/voxels/Chunk.hpp>
#include <quartz/voxels/terrain/PerlinNoise.hpp>

namespace qz
{
	namespace voxels
	{
		class ChunkManager
		{
		public:
			ChunkManager(const std::string& blockID, int chunkSize, unsigned int seed);
			ChunkManager(ChunkManager&& other) = default;

			~ChunkManager() = default;

			void toggleWireframe();
			bool isWireframe() const;;

			void determineGeneration(qz::Vector3 cameraPosition);
			void testGeneration();
			void unloadRedundant();

			void setBlockAt(qz::Vector3 position, const BlockInstance& block);
			BlockInstance getBlockAt(qz::Vector3 position) const;

			void breakBlockAt(qz::Vector3 position, const BlockInstance& block);
			void placeBlockAt(qz::Vector3 position, const BlockInstance& block);
						
			void render(int bufferCounter);

		private:
			unsigned int m_seed;
			int m_chunkSize;
			std::string m_defaultBlockID;

			std::vector<Chunk> m_chunks;

			bool m_wireframe = false;
		};

	}
}
