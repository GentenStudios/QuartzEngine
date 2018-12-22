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
			ChunkManager(const std::string& blockID);
			~ChunkManager();

			void toggleWireframe();
			bool isWireframe() { return m_wireframe; };

			void determineGeneration(phx::Vector3 cameraPosition);
			void generateChunkAt(phx::Vector3 chunkPos);
			void testGeneration(int test);
			void unloadRedundant() { /* TODO this. */ }

			void setBlockAt(phx::Vector3 position, const BlockInstance& block);
			BlockInstance getBlockAt(phx::Vector3 position);

			void breakBlockAt(phx::Vector3 position, const BlockInstance& block);
			void placeBlockAt(phx::Vector3 position, const BlockInstance& block);
						
			void render(int bufferCounter);

		private:
			PerlinNoise* m_terrainGenerator;

			ChunkContainer* m_managerData;
			std::string m_defaultBlockID;

			bool m_wireframe = false;
		};

	}
}
