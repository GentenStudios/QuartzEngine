//#pragma once
//
//#include <engine/core/Core.hpp>
//
//#include <engine/voxels/Block.hpp>
//#include <engine/voxels/Chunk.hpp>
//
//namespace phx
//{
//	namespace voxels
//	{
//		struct ChunkContainer
//		{
//			std::vector<Chunk> chunks;
//			std::vector<Vector3> positions;
//		};
//
//		class ChunkManager
//		{
//		public:
//			ChunkManager();
//			~ChunkManager();
//
//			void setDefaultBlock(Block* block);
//
//			void toggleWireframe();
//			bool isWireframe() { return m_wireframe; };
//
//			void determineGeneration(int test);
//			void testGeneration(int test);
//			void unloadRedundant() { /* TODO this. */ }
//
//			void setBlockAt(phx::Vector3 position, Block* block);
//			Block* getBlockAt(phx::Vector3 position);
//
//
//			void breakBlockAt(phx::Vector3 position);
//			void placeBlockAt(phx::Vector3 position, Block* block);
//						
//			void render(int bufferCounter);
//
//		private:
//			ChunkContainer* m_managerData;
//			Block* m_defaultBlock;
//
//			bool m_wireframe;
//		};
//
//	}
//}