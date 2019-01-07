#pragma once

#include <engine/core/Core.hpp>

#include <engine/voxels/Block.hpp>
#include <engine/voxels/Chunk.hpp>
#include "terrain/PerlinNoise.hpp"

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
			ChunkManager(std::string blockID, unsigned int chunkSize, unsigned int seed);
			ChunkManager(const ChunkManager&) = default;

			~ChunkManager() = default;

			void toggleWireframe();
			bool isWireframe() const;;

			void determineGeneration(phx::Vector3 cameraPosition);
			void testGeneration(int test);
			void unloadRedundant();

			void setBlockAt(phx::Vector3 position, const BlockInstance& block);
			BlockInstance getBlockAt(phx::Vector3 position) const;

			void breakBlockAt(phx::Vector3 position, const BlockInstance& block);
			void placeBlockAt(phx::Vector3 position, const BlockInstance& block);
						
			void render(int bufferCounter) const;

		private:
			unsigned int m_seed;

			unsigned int m_chunkSize;

			ChunkContainer* m_managerData;
			std::string m_defaultBlockID;

			bool m_wireframe = false;
		};

	}
}
