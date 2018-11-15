#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/math/Vector2.hpp>
#include <engine/core/math/Vector3.hpp>

#include <engine/voxels/Block.hpp>

#include <engine/core/graphics/gl/VertexBuffer.hpp>
#include <engine/core/graphics/gl/VertexArray.hpp>
#include <engine/core/graphics/gl/VertexAttrib.hpp>
#include <engine/core/graphics/gl/TextureArray.hpp>

namespace phx
{
	namespace voxels
	{
		enum ChunkFlags : unsigned char
		{
			NEEDS_BUFFERING	= 1 << 0,
			NEEDS_MESHING	= 1 << 1,
			NEEDS_TEXTURING	= 1 << 2,
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
		};

		class Chunk
		{
		public:
			Chunk(const Chunk&) = default;

			Chunk(phx::Vector3 chunkPos, unsigned int chunkSize, Block* defaultBlock);
			~Chunk() {}

			void populateData();  // should update the chunk mesh for the chunk renderer

			void buildMesh();  // should update the meshes
			void rebuildMeshAt(phx::Vector3 position);


			void addBlockFace(BlockFace face, int memOffset, int x, int y, int z);

			void breakBlockAt(phx::Vector3 position, Block* replaceBlock);
			void placeBlockAt(phx::Vector3 position, Block* placeBlock);

			const Block* getBlockAt(phx::Vector3 position);
			void setBlockAt(phx::Vector3 position, Block* block);

			void buildTextureArray();
			void bufferData();
			void render(int* counter);

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

			phx::gfx::gl::TextureArray* m_textureArray = nullptr;
			
			Mesh* m_blockMesh;
			Mesh* m_objectMesh;
			Mesh* m_waterMesh;

			phx::gfx::gl::VertexArray* m_vao = nullptr;
			phx::gfx::gl::VertexBuffer* m_vbo = nullptr;
			phx::gfx::gl::VertexBuffer* m_uvbo = nullptr;
			phx::gfx::gl::VertexBuffer* m_tlbo = nullptr; // Texture Layer Buffer Object

			unsigned int m_vertInChunk;
			unsigned int m_normalInChunk;
			unsigned int m_uvInChunk;
			unsigned int m_layersInChunk;
		};

	}
}