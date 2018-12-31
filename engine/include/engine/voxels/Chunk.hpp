#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/math/Vector2.hpp>
#include <engine/core/math/Vector3.hpp>

#include <engine/voxels/Block.hpp>
#include <engine/voxels/terrain/PerlinNoise.hpp>

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
			BLOCKS_NEED_BUFFERING	= 1 << 0,
			OBJECTS_NEED_BUFFERING	= 1 << 1,
			WATER_NEEDS_BUFFERING	= 1 << 2,
			NEEDS_MESHING			= 1 << 3,
			NEEDS_TEXTURING			= 1 << 4
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
			std::vector<phx::Vector3> vertices;
			std::vector<phx::Vector3> normals;
			std::vector<phx::Vector2> uvs;
			std::vector<int> texLayers;

			void reset();
			void update(const Mesh& other);

			std::size_t triangleCount() const;
		};

		class ChunkMesh
		{
		public:
			ChunkMesh();
			~ChunkMesh();

			void add(const BlockInstance& block, BlockFace face, phx::Vector3 chunkPos, phx::Vector3 blockPos);

			const Mesh& getBlockMesh() const;
			const Mesh& getObjectMesh() const;
			const Mesh& getWaterMesh() const;

			void resetAll();

		private:
			Mesh m_blockMesh;
			Mesh m_objectMesh;
			Mesh m_waterMesh;
		};

		class ChunkRenderer
		{
		public:
			ChunkRenderer();
			~ChunkRenderer();

			void resetMesh();
			void updateMesh(const Mesh& mesh);

			void bufferData();
			void render();

			std::size_t getTrianglesCount() const;

		private:
			Mesh m_mesh;

			gfx::gl::VertexArray* m_vao;
			gfx::gl::VertexBuffer* m_vbo;

			gfx::gl::TextureArray* m_textureArray = nullptr;
		};

		class Chunk
		{
		public:
			Chunk() = delete;
			Chunk(const Chunk&) = default;
			Chunk(Chunk&& o) = default;
			Chunk(phx::Vector3 chunkPos, unsigned int chunkSize, const std::string& defaultBlockID);

			~Chunk() = default;

			void populateData(unsigned int seed);

			void buildMesh();

			const ChunkMesh& getChunkMesh() const;
			const Vector3& getChunkPos() const;

			void breakBlockAt(phx::Vector3 position, const BlockInstance& block);
			void placeBlockAt(phx::Vector3 position, const BlockInstance& block);

			BlockInstance getBlockAt(phx::Vector3 position) const;
			void setBlockAt(phx::Vector3 position, const BlockInstance& newBlock);

			void renderBlocks(int* counter);
			void renderObjects(int* counter);
			void renderWater(int* counter);

		private:
			phx::Vector3 m_chunkPos;
			unsigned int m_chunkSize;

			ChunkMesh m_mesh;

			ChunkRenderer m_blockRenderer;

			// These are for later, when we support objects and water :)
			//ChunkRenderer m_objectRenderer;
			//ChunkRenderer m_waterRenderer;

			unsigned char m_chunkFlags = 0;

			std::string m_defaultBlockID;
			std::vector<BlockInstance> m_chunkBlocks;

			std::size_t getVectorIndex(std::size_t x, std::size_t y, std::size_t z) const
			{
				return x + m_chunkSize * (y + m_chunkSize * z);
			}
		};

	}
}