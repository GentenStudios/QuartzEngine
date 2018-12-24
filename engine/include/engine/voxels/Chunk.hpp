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
			Chunk() = delete;
			Chunk(const Chunk&) = default;
			Chunk(Chunk&& o) = default;
			Chunk(phx::Vector3 chunkPos, unsigned int chunkSize, const std::string& defaultBlockID);

			~Chunk() = default;

			void populateData(unsigned int seed);

			void buildMesh(); 

			void addBlockFace(BlockFace face, int x, int y, int z);

			void breakBlockAt(phx::Vector3 position, const BlockInstance& block);
			void placeBlockAt(phx::Vector3 position, const BlockInstance& block);

			BlockInstance getBlockAt(phx::Vector3 position) const;
			void setBlockAt(phx::Vector3 position, const BlockInstance& newBlock);

			void bufferData();
			void render(int* counter);

			inline const Vector3& getChunkPos() const { return m_chunkPos; }

		private:
			phx::Vector3 m_chunkPos;
			unsigned int m_chunkSize;

			unsigned char m_chunkFlags = 0;

			std::string m_defaultBlockID;
			std::vector<std::vector<std::vector<BlockInstance>>> m_chunkBlocks;

			phx::gfx::gl::TextureArray* m_textureArray = nullptr;
			
			Mesh* m_blockMesh;
			Mesh* m_objectMesh;
			Mesh* m_waterMesh;

			phx::gfx::gl::VertexArray* m_vao = nullptr;
			phx::gfx::gl::VertexBuffer* m_vbo = nullptr;
			phx::gfx::gl::VertexBuffer* m_uvbo = nullptr;
			phx::gfx::gl::VertexBuffer* m_tlbo = nullptr; // Texture Layer Buffer Object
		};

	}
}