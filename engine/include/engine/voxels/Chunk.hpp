#pragma once

#include "engine/common.hpp"
#include "engine/math/Vector3.hpp"
#include "engine/math/Vector2.hpp"

#include "engine/voxels/Block.hpp"

#include "engine/graphics/opengl/VertexBuffer.hpp"
#include "engine/graphics/opengl/VertexArray.hpp"
#include "engine/graphics/opengl/VertexAttrib.hpp"

#include <atomic>

namespace phx
{
	namespace voxels
	{
		enum ChunkFlags : unsigned char
		{
			NEEDS_BUFFERING	= 1 << 0,
			NEEDS_MESHING	= 1 << 1,
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
			std::vector<phx::Vector3> chunkVertices;
			std::vector<phx::Vector3> chunkNormals;
			std::vector<phx::Vector2> chunkUVs;
			std::vector<int> chunkTexLayers;

			void reset();
			void update(const Mesh& mesh);
		};

		class Chunk
		{
		public:
			Chunk(const Chunk&) = default;

			Chunk(phx::Vector3 chunkPos, unsigned int chunkSize, Block* defaultBlock);
			~Chunk() {}

			void populateData();  // should update the chunk mesh for the chunk renderer

			void buildMesh();  // should update the meshes

			void addBlockFace(BlockFace face, int memOffset, int x, int y, int z);
			void removeBlockFace(BlockFace face, int memOffset, int x, int y, int z);

			void bufferData();
			void render(int* counter);

			void breakBlockAt(phx::Vector3 position, Block* replaceBlock);
			void placeBlockAt(phx::Vector3 position);

			const Block* getBlockAt(phx::Vector3 position);
			void setBlockAt(phx::Vector3 position, Block* block);

			const Vector3& getChunkPos() { return m_chunkPos; }

			Mesh* getBlocksMesh();
			Mesh* getObjectsMesh();
			Mesh* getWaterMesh();

		private:
			phx::Vector3 m_chunkPos;
			unsigned int m_chunkSize;

			unsigned char m_chunkFlags = 0;

			Block* m_defaultBlock;
			std::vector<std::vector<std::vector<Block*>>> m_chunkBlocks;
			
			Mesh* m_blockMesh;
			Mesh* m_objectMesh;
			Mesh* m_waterMesh;

			phx::gfx::gl::VertexArray* m_vao = nullptr;
			phx::gfx::gl::VertexBuffer* m_vbo = nullptr;

			unsigned int m_vertInChunk;
			unsigned int m_normalInChunk;
			unsigned int m_uvInChunk;
			unsigned int m_layersInChunk;
		};

	}
}