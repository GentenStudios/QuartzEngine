#pragma once

#include <engine/core/utils/ThreadPool.hpp>

#include <engine/voxels/Block.hpp>
#include <engine/voxels/Chunk.hpp>
#include <engine/voxels/terrain/PerlinNoise.hpp>

namespace phx
{
	namespace voxels
	{
		struct ChunkContainer
		{
			
		};

		class ChunkManager
		{
		public:
			ChunkManager(const std::string& blockID, unsigned int chunkSize, unsigned int seed);
			ChunkManager(ChunkManager&& other) = default;

			~ChunkManager() = default;

			void toggleWireframe();
			bool isWireframe() const;;

			void determineGeneration(phx::Vector3 cameraPosition);
			void testGeneration();
			void unloadRedundant();

			void setBlockAt(phx::Vector3 position, const BlockInstance& block);
			BlockInstance getBlockAt(phx::Vector3 position) const;

			void breakBlockAt(phx::Vector3 position, const BlockInstance& block);
			void placeBlockAt(phx::Vector3 position, const BlockInstance& block);
						
			void render(int bufferCounter);

		private:
			unsigned int m_seed;

			unsigned int m_chunkSize;

			std::string m_defaultBlockID;

			std::vector<Chunk> m_chunks;

			bool m_wireframe = false;

			threads::ThreadPool<10> m_threadPool;
			std::mutex m_mutex;

			void addChunkToArray(const Chunk& chunk);
		};

	}
}
