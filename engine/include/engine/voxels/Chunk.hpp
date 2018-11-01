#pragma once

#include "engine/common.hpp"
#include "engine/math/Vector3.hpp"
#include "engine/math/Vector2.hpp"

#include "engine/voxels/Block.hpp"

#include "engine/graphics/opengl/VertexBuffer.hpp"
#include "engine/graphics/opengl/VertexArray.hpp"
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

		class ChunkMesh
		{
		public:
			ChunkMesh();
			~ChunkMesh() {}

			void addBlockFace(BlockFace face, int memOffset, int x, int y, int z);
			void removeBlockFace(BlockFace face, int memOffset, int x, int y, int z);
			void setMeshPos(Vector3& chunkPos);

			Mesh* getBlocksMesh();
			Mesh* getObjectsMesh();
			Mesh* getWaterMesh();

		private:
			Vector3 m_chunkPos;

			// first mesh is for blocks
			// second is for objects, we will draw them with another shader to add transparency support and have better performances
			// last one is for water since we need a specific shader for this shit to add beautiful flying and moving waves (and apply face culling)
			Mesh* m_blocks;
			Mesh* m_objects;
			Mesh* m_water;
		};

		class Chunk
		{
		public:
			Chunk(phx::Vector3 chunkPos, unsigned int chunkSize, Block* defaultBlock);
			~Chunk() {}

			void populateData();  // should update the chunk mesh for the chunk renderer

			void buildMesh();  // should update the meshes

			void breakBlockAt(phx::Vector3 position, Block* replaceBlock);
			void placeBlockAt(phx::Vector3 position);

			Block* getBlockAt(phx::Vector3 position);
			void setBlockAt(phx::Vector3 position, Block* block);

			ChunkMesh* getChunkMesh();

			ChunkData* getChunkDataPointer() { return m_chunkData; }

		private:
			Block* m_defaultBlock;
			ChunkData* m_chunkData;
			ChunkMesh* m_mesh;

			unsigned int m_vertInChunk;
			unsigned int m_normalInChunk;
			unsigned int m_uvInChunk;
			unsigned int m_layersInChunk;
		};

		class ChunkRenderer
		{
		public:
			ChunkRenderer();
			~ChunkRenderer() {};

			void attachChunk(Chunk* chunkPointer);

			void bufferData();
			void render();

			std::size_t getTrianglesCount() const;

		private:
			phx::gfx::gl::VertexArray* m_vao;
			phx::gfx::gl::VertexBuffer* m_vbo;
			phx::gfx::gl::VertexBuffer* m_uvbo;

			std::vector<Chunk*> m_chunks;
		};


	}
}