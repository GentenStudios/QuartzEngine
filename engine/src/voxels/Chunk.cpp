#include <engine/voxels/Chunk.hpp>

#include <engine/voxels/terrain/PerlinNoise.hpp>

#include <cstring>
#include <functional>
#include <numeric>

using namespace phx::voxels;
using namespace phx;

static const Vector3 CUBE_VERTS[] = {
	// front
	Vector3(-1.f, -1.f, -1.f),
	Vector3(1.f, -1.f, -1.f),
	Vector3(1.f,  1.f, -1.f),
	Vector3(1.f,  1.f, -1.f),
	Vector3(-1.f,  1.f, -1.f),
	Vector3(-1.f, -1.f, -1.f),

	// back
	Vector3(-1.f, -1.f, 1.f),
	Vector3(1.f, -1.f, 1.f),
	Vector3(1.f,  1.f, 1.f),
	Vector3(1.f,  1.f, 1.f),
	Vector3(-1.f,  1.f, 1.f),
	Vector3(-1.f, -1.f, 1.f),

	// left
	Vector3(-1.f,  1.f,  1.f),
	Vector3(-1.f,  1.f, -1.f),
	Vector3(-1.f, -1.f, -1.f),
	Vector3(-1.f, -1.f, -1.f),
	Vector3(-1.f, -1.f,  1.f),
	Vector3(-1.f,  1.f,  1.f),

	// right
	Vector3(1.f,  1.f,  1.f),
	Vector3(1.f,  1.f, -1.f),
	Vector3(1.f, -1.f, -1.f),
	Vector3(1.f, -1.f, -1.f),
	Vector3(1.f, -1.f,  1.f),
	Vector3(1.f,  1.f,  1.f),

	// bottom
	Vector3(-1.f, -1.f, -1.f),
	Vector3(1.f, -1.f, -1.f),
	Vector3(1.f, -1.f,  1.f),
	Vector3(1.f, -1.f,  1.f),
	Vector3(-1.f, -1.f,  1.f),
	Vector3(-1.f, -1.f, -1.f),

	// top
	Vector3(-1.f,  1.f, -1.f),
	Vector3(1.f,  1.f, -1.f),
	Vector3(1.f,  1.f,  1.f),
	Vector3(1.f,  1.f,  1.f),
	Vector3(-1.f,  1.f,  1.f),
	Vector3(-1.f,  1.f, -1.f)
};

static const Vector2 CUBE_UV[] = {
	// front north
	Vector2(-0.f, 1.f),
	Vector2(-1.f, 1.f),
	Vector2(-1.f, 0.f),
	Vector2(-1.f, 0.f),
	Vector2(-0.f, 0.f),
	Vector2(-0.f, 1.f),

	// back south
	Vector2(0.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(0.f, 0.f),
	Vector2(0.f, 1.f),

	// left west
	Vector2(-0.f, 0.f),
	Vector2(-1.f, 0.f),
	Vector2(-1.f, 1.f),
	Vector2(-1.f, 1.f),
	Vector2(-0.f, 1.f),
	Vector2(-0.f, 0.f),

	// right east
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),

	// bottom
	Vector2(0.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(0.f, 0.f),
	Vector2(0.f, 1.f),

	// top
	Vector2(0.f, -1.f),
	Vector2(1.f, -1.f),
	Vector2(1.f, -0.f),
	Vector2(1.f, -0.f),
	Vector2(0.f, -0.f),
	Vector2(0.f, -1.f),
};

Chunk::Chunk(Vector3 chunkPos, unsigned int chunkSize, const std::string& defaultBlockID)
{
	m_defaultBlockID = defaultBlockID;

	m_blockMesh = new Mesh();
	m_objectMesh = new Mesh();
	m_waterMesh = new Mesh();

	m_textureArray = new gfx::gl::TextureArray();

	m_chunkPos = chunkPos;
	m_chunkSize = chunkSize;

	m_chunkFlags = NEEDS_BUFFERING | NEEDS_MESHING;
}

void Chunk::populateData(unsigned int seed)
{
	// Set whole array to have, for example, 16 elements inside the vector.
	m_chunkBlocks.resize(m_chunkSize);

	for (auto& x : m_chunkBlocks)
	{
		// Set each X index (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][0] to m_chunkBlocks[x][15]
		x.resize(m_chunkSize);
		for (auto& y : x)
		{
			// Set the Y (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][y][0] to m_chunkBlocks[x][y][15]
			y.resize(m_chunkSize);
			for (auto& z : y)
			{
				// Set the Z (first vector part, of the trio) to have the actual value of the blocks data. So, you can have m_chunkBlocks[x][y][z] = BlockInstance("blah:blah")
				z = BlockInstance("core:air");
			}
		}
	}

	PerlinNoise* terrainGenerator = new PerlinNoise(seed);
	terrainGenerator->generateFor(m_chunkBlocks, m_chunkPos);
	delete terrainGenerator;
}

void Chunk::buildMesh()
{
	m_blockMesh->chunkVertices.clear();
	m_blockMesh->chunkTexLayers.clear();
	m_blockMesh->chunkUVs.clear();

	for (unsigned int z = 0; z < m_chunkSize; z++)
	{
		for (unsigned int y = 0; y < m_chunkSize; y++)
		{
			for (unsigned int x = 0; x < m_chunkSize; x++)
			{
				if (m_chunkBlocks[x][y][z].getBlockType() == BlockType::GAS)
					continue;

				if (x == 0 || m_chunkBlocks[x - 1][y][z].getBlockType() != BlockType::SOLID)
					addBlockFace(BlockFace::RIGHT,	x, y, z);
				if (x == m_chunkSize - 1 || m_chunkBlocks[x + 1][y][z].getBlockType() != BlockType::SOLID)
					addBlockFace(BlockFace::LEFT,	x, y, z);

				if (y == 0 || m_chunkBlocks[x][y - 1][z].getBlockType() != BlockType::SOLID)
					addBlockFace(BlockFace::BOTTOM,	x, y, z);
				if (y == m_chunkSize - 1 || m_chunkBlocks[x][y + 1][z].getBlockType() != BlockType::SOLID)
					addBlockFace(BlockFace::TOP,	x, y, z);

				if (z == 0 || m_chunkBlocks[x][y][z - 1].getBlockType() != BlockType::SOLID)
					addBlockFace(BlockFace::FRONT,	x, y, z);
				if (z == m_chunkSize - 1 || m_chunkBlocks[x][y][z + 1].getBlockType() != BlockType::SOLID)
					addBlockFace(BlockFace::BACK,	x, y, z);
			}
		}
	}

	m_chunkFlags &= ~NEEDS_MESHING;
	if (!(m_chunkFlags & NEEDS_BUFFERING))
		m_chunkFlags |= NEEDS_BUFFERING;
}

void Chunk::addBlockFace(BlockFace face, int x, int y, int z)
{
	auto& blockTex = m_chunkBlocks[x][y][z].getBlockTextures();
	int texLayer = 0;

	if (static_cast<size_t>(face) < blockTex.size())
	{
		m_textureArray->add(blockTex[static_cast<int>(face)]);
		texLayer = m_textureArray->getTexLayer(blockTex[static_cast<int>(face)]);
	}

	for (int i = 0; i < 6; i++)
	{
		phx::Vector3 temp = CUBE_VERTS[(static_cast<int>(face) * 6) + i];
		temp.x += (x * 2) + (m_chunkPos.x * 2); // Multiply by 2, as that is the size of the actual cube edges, indicated by the cube vertices.
		temp.y += (y * 2) + (m_chunkPos.y * 2);
		temp.z += (z * 2) + (m_chunkPos.z * 2);

		phx::Vector2 temp2 = CUBE_UV[(static_cast<int>(face) * 6) + i];

		m_blockMesh->chunkVertices.push_back(temp);
		m_blockMesh->chunkUVs.push_back(temp2);
		m_blockMesh->chunkTexLayers.push_back(texLayer);
	}
}

void Chunk::breakBlockAt(phx::Vector3 position, const BlockInstance& block)
{
	position.floor();
	if (position.x < m_chunkSize)
	{
		if (position.y < m_chunkSize)
		{
			if (position.z < m_chunkSize)
			{
				auto& breakCallback = BlockLibrary::get()->requestBlock(m_chunkBlocks[static_cast<int>(position.x)][static_cast<int>(position.y)][static_cast<int>(position.z)].getBlockID()).getBreakCallback();
				if (breakCallback != nullptr)
					breakCallback();

				m_chunkBlocks[static_cast<int>(position.x)][static_cast<int>(position.y)][static_cast<int>(position.z)] = block;

				if (!(m_chunkFlags & NEEDS_MESHING))
					m_chunkFlags |= NEEDS_MESHING;
			}
		}
	}
}

void Chunk::placeBlockAt(phx::Vector3 position, const BlockInstance& block)
{
	position.floor();
	if (position.x < m_chunkSize)
	{
		if (position.y < m_chunkSize)
		{
			if (position.z < m_chunkSize)
			{
				auto& placeCallback = BlockLibrary::get()->requestBlock(block.getBlockID()).getPlaceCallback();
				if (placeCallback != nullptr)
					placeCallback();

				m_chunkBlocks[static_cast<int>(position.x)][static_cast<int>(position.y)][static_cast<int>(position.z)] = block;

				if (!(m_chunkFlags & NEEDS_MESHING))
					m_chunkFlags |= NEEDS_MESHING;
			}
		}
	}
}

BlockInstance Chunk::getBlockAt(phx::Vector3 position) const
{
	position.floor();
	if (position.x < m_chunkSize)
	{
		if (position.y < m_chunkSize)
		{
			if (position.z < m_chunkSize)
			{
				return m_chunkBlocks[static_cast<int>(position.x)][static_cast<int>(position.y)][static_cast<int>(position.z)];
			}
		}
	}

	return BlockInstance("core:out_of_bounds");
}

void Chunk::setBlockAt(phx::Vector3 position, const BlockInstance& newBlock)
{
	position.floor();
	if (position.x < m_chunkSize)
	{
		if (position.y < m_chunkSize)
		{
			if (position.z < m_chunkSize)
			{
				m_chunkBlocks[static_cast<int>(position.x)][static_cast<int>(position.y)][static_cast<int>(position.z)] = newBlock;

				if (!(m_chunkFlags & NEEDS_MESHING))
					m_chunkFlags |= NEEDS_MESHING;
			}
		}
	}
}

void Chunk::bufferData()
{
	if (m_vao == nullptr)
		m_vao = new gfx::gl::VertexArray();

	m_vao->bind();

	if (m_vbo == nullptr)
		m_vbo = new gfx::gl::VertexBuffer(gfx::gl::BufferTarget::ARRAY_BUFFER, gfx::gl::BufferUsage::DYNAMIC_DRAW);

	if (m_uvbo == nullptr)
		m_uvbo = new gfx::gl::VertexBuffer(gfx::gl::BufferTarget::ARRAY_BUFFER, gfx::gl::BufferUsage::DYNAMIC_DRAW);

	if (m_tlbo == nullptr)
		m_tlbo = new gfx::gl::VertexBuffer(gfx::gl::BufferTarget::ARRAY_BUFFER, gfx::gl::BufferUsage::DYNAMIC_DRAW);

	m_vbo->bind();
	m_vbo->setData(static_cast<void*>(m_blockMesh->chunkVertices.data()), sizeof(m_blockMesh->chunkVertices[0]) * m_blockMesh->chunkVertices.size());

	gfx::gl::VertexAttrib vertices(0, 3, 3*sizeof(float), 0, gfx::gl::GLType::FLOAT);
	vertices.enable();

	m_uvbo->bind();
	m_uvbo->setData(static_cast<void*>(m_blockMesh->chunkUVs.data()), sizeof(m_blockMesh->chunkUVs[0]) * m_blockMesh->chunkUVs.size());

	gfx::gl::VertexAttrib uvs(1, 2, 2*sizeof(float), 0, gfx::gl::GLType::FLOAT);
	uvs.enable();

	m_tlbo->bind();
	m_tlbo->setData(static_cast<void*>(m_blockMesh->chunkTexLayers.data()), sizeof(m_blockMesh->chunkTexLayers[0]) * m_blockMesh->chunkTexLayers.size());

	gfx::gl::VertexAttrib texLayers(2, 1, sizeof(float), 0, gfx::gl::GLType::FLOAT);
	texLayers.enable();

	m_chunkFlags &= ~NEEDS_BUFFERING;
}

void Chunk::render(int* counter)
{
	if (m_chunkFlags & NEEDS_BUFFERING)
	{
		if ((*counter) == 0)
			return;
		LDEBUG("BUFFERING MESH DATA!");
		bufferData();
		(*counter)--;
	}

	if (!m_blockMesh->chunkVertices.empty())
	{
		m_textureArray->bind(10);
		m_vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, m_blockMesh->chunkVertices.size());
		m_textureArray->unbind();
		m_vao->unbind();
	}

	if (m_chunkFlags & NEEDS_MESHING)
	{
		if ((*counter) == 0)
			return;
		LDEBUG("BUILDING MESH!");
		buildMesh();
		(*counter)--;
	}

}