#include <engine/voxels/Chunk.hpp>

#include <cstring>
#include <functional>
#include <numeric>

using namespace phx::voxels;
using namespace phx;

static const Vector2 CubeUV[] = {
	// front
	Vector2(0.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(0.f, 0.f),
	Vector2(0.f, 1.f),

	// back
	Vector2(0.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(0.f, 0.f),
	Vector2(0.f, 1.f),

	// left
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),

	// right
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
	Vector2(0.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(0.f, 0.f),
	Vector2(0.f, 1.f),
};

static const Vector3 CubeVerts[] = {
	// front
	Vector3(-1.f, -1.f, -1.f),
	Vector3( 1.f, -1.f, -1.f),
	Vector3( 1.f,  1.f, -1.f),
	Vector3( 1.f,  1.f, -1.f),
	Vector3(-1.f,  1.f, -1.f),
	Vector3(-1.f, -1.f, -1.f),

	// back
	Vector3(-1.f, -1.f, 1.f),
	Vector3( 1.f, -1.f, 1.f),
	Vector3( 1.f,  1.f, 1.f),
	Vector3( 1.f,  1.f, 1.f),
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
	Vector3( 1.f, -1.f, -1.f),
	Vector3( 1.f, -1.f,  1.f),
	Vector3( 1.f, -1.f,  1.f),
	Vector3(-1.f, -1.f,  1.f),
	Vector3(-1.f, -1.f, -1.f),

	// top
	Vector3(-1.f,  1.f, -1.f),
	Vector3( 1.f,  1.f, -1.f),
	Vector3( 1.f,  1.f,  1.f),
	Vector3( 1.f,  1.f,  1.f),
	Vector3(-1.f,  1.f,  1.f),
	Vector3(-1.f,  1.f, -1.f)
};

Chunk::Chunk(Vector3 chunkPos, unsigned int chunkSize, const std::string& defaultBlock)
{
	m_defaultBlockID = defaultBlock;
	
	m_blockMesh = new Mesh();
	m_objectMesh = new Mesh();
	m_waterMesh = new Mesh();

	m_textureArray = new gfx::gl::TextureArray();

	m_chunkPos = chunkPos;
	m_chunkSize = chunkSize;

	unsigned int sizeCubed = chunkSize * chunkSize * chunkSize;
	m_vertInChunk = sizeCubed * 36;
	m_uvInChunk = sizeCubed * 36;

	m_blockMesh->chunkVertices.resize(m_vertInChunk);
	m_blockMesh->chunkTexLayers.resize(m_vertInChunk);
	m_blockMesh->chunkUVs.resize(m_uvInChunk);

	m_chunkFlags = NEEDS_BUFFERING | NEEDS_MESHING;

}

void Chunk::populateData()
{
	// Set whole array to have, for example, 16 elements inside the vector.
	m_chunkBlocks.resize(m_chunkSize);

	for (unsigned int x = 0; x < m_chunkBlocks.size(); x++)
	{
		// Set each X index (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][0] to m_chunkBlocks[x][15]
		m_chunkBlocks[x].resize(m_chunkSize);
		for (unsigned int y = 0; y < m_chunkBlocks[x].size(); y++)
		{
			// Set the Y (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][y][0] to m_chunkBlocks[x][y][15]
			m_chunkBlocks[x][y].resize(m_chunkSize);
			for (unsigned int z = 0; z < m_chunkBlocks[x][y].size(); z++)
			{
				// Set the Z (first vector part, of the trio) to have the actual value of the blocks data. So, you can have m_chunkBlocks[x][y][z] = BlockType::SOLID
				m_chunkBlocks[x][y][z] = BlockInstance(m_defaultBlockID);
			}
		}
	}
}

void Chunk::buildMesh()
{
	for (unsigned int z = 0; z < m_chunkSize; z++)
	{
		for (unsigned int y = 0; y < m_chunkSize; y++)
		{
			for (unsigned int x = 0; x < m_chunkSize; x++)
			{
				if (m_chunkBlocks[x][y][z].getBlockType() != BlockType::OBJECT && m_chunkBlocks[x][y][z].getBlockType() != BlockType::WATER)
				{

					int memOffset = (x * 36) + (m_chunkSize * ((y * 36) + m_chunkSize * (z * 36)));

					std::memset(m_blockMesh->chunkVertices.data() + memOffset, 0, sizeof(CubeVerts));
					std::memset(m_blockMesh->chunkTexLayers.data() + memOffset, 0, 36 * sizeof(int));
					std::memcpy(m_blockMesh->chunkUVs.data() + memOffset, CubeUV, sizeof(CubeUV));

					if (m_chunkBlocks[x][y][z].getBlockType() == BlockType::GAS)
						continue;

					if (x == 0 || m_chunkBlocks[x - 1][y][z].getBlockType() != BlockType::SOLID)
						addBlockFace(BlockFace::RIGHT, memOffset, x, y, z);
					if (x == m_chunkSize - 1 || m_chunkBlocks[x + 1][y][z].getBlockType() != BlockType::SOLID)
						addBlockFace(BlockFace::LEFT, memOffset, x, y, z);

					if (y == 0 || m_chunkBlocks[x][y - 1][z].getBlockType() != BlockType::SOLID)
						addBlockFace(BlockFace::BOTTOM, memOffset, x, y, z);
					if (y == m_chunkSize - 1 || m_chunkBlocks[x][y + 1][z].getBlockType() != BlockType::SOLID)
						addBlockFace(BlockFace::TOP, memOffset, x, y, z);

					if (z == 0 || m_chunkBlocks[x][y][z - 1].getBlockType() != BlockType::SOLID)
						addBlockFace(BlockFace::FRONT, memOffset, x, y, z);
					if (z == m_chunkSize - 1 || m_chunkBlocks[x][y][z + 1].getBlockType() != BlockType::SOLID)
						addBlockFace(BlockFace::BACK, memOffset, x, y, z);

				}
				else if (m_chunkBlocks[x][y][z].getBlockType() == BlockType::WATER)
				{
					//TODO: all of this shit.
				}
			}
		}
	}

	m_chunkFlags &= ~NEEDS_MESHING;
	if(!(m_chunkFlags & NEEDS_BUFFERING))
		m_chunkFlags |= NEEDS_BUFFERING;
}

void Chunk::addBlockFace(BlockFace face, int memOffset, int x, int y, int z)
{
	int bytesInFace = 6 * sizeof(Vector3);
	int memOffsetOffest = static_cast<int>(face) * 6;

	std::memcpy(m_blockMesh->chunkVertices.data() + memOffset + memOffsetOffest,	// Position in memory to copy to. So... original memory location + memory offset for that block + memory offset for that face.
		CubeVerts + memOffsetOffest,												// Data to copy, PLUS, the memory offset, so the correct portion of the block is copied.
		bytesInFace																	// Size of Data to copy.
	);

	auto& blockTex = m_chunkBlocks[x][y][z].getBlockTextures();
	int texLayer = 0;

	if (static_cast<int>(face) < blockTex.size())
	{
		m_textureArray->add(blockTex[static_cast<int>(face)]);
		texLayer = m_textureArray->getTexLayer(blockTex[static_cast<int>(face)]);
	}

	// Set block positions in world space
	for (int q = memOffset + memOffsetOffest; q < memOffset + memOffsetOffest + 6; q++)
	{
		m_blockMesh->chunkTexLayers[q] = texLayer; // Set the texture layer
		m_blockMesh->chunkVertices[q].x += (x * 2) + (m_chunkPos.x * 2); // Multiply by 2, as that is the size of the actual cube edges, indicated by the cube vertices.
		m_blockMesh->chunkVertices[q].y += (y * 2) + (m_chunkPos.y * 2);
		m_blockMesh->chunkVertices[q].z += (z * 2) + (m_chunkPos.z * 2);
	}
}

void Chunk::breakBlockAt(phx::Vector3 position, const BlockInstance& block)
{
	if (position.x < m_chunkBlocks.size())
	{
		if (position.y < m_chunkBlocks[position.x].size())
		{
			if (position.z < m_chunkBlocks[position.z].size())
			{
				int memOffset = (position.x * 36) + (m_chunkSize * ((position.y * 36) + m_chunkSize * (position.z * 36)));
				std::memset(m_blockMesh->chunkVertices.data() + memOffset, 0, sizeof(CubeVerts));

				auto& breakCallback =  BlockLibrary::get()->requestBlock(m_chunkBlocks[position.x][position.y][position.z].getBlockID()).getBreakCallback();
				if (breakCallback != nullptr)
					breakCallback();

				m_chunkBlocks[position.x][position.y][position.z] = block;
				
				if (!(m_chunkFlags & NEEDS_MESHING))
					m_chunkFlags |= NEEDS_MESHING;
			}
		}
	}
}

void Chunk::placeBlockAt(phx::Vector3 position, const BlockInstance& block)
{
	if (position.x < m_chunkBlocks.size())
	{
		if (position.y < m_chunkBlocks[position.x].size())
		{
			if (position.z < m_chunkBlocks[position.z].size())
			{
				int memOffset = (position.x * 36) + (m_chunkSize * ((position.y * 36) + m_chunkSize * (position.z * 36)));
				std::memcpy(m_blockMesh->chunkVertices.data() + memOffset, CubeVerts, sizeof(CubeVerts));

				auto& placeCallback = BlockLibrary::get()->requestBlock(block.getBlockID()).getPlaceCallback();
				if (placeCallback != nullptr)
					placeCallback();

				m_chunkBlocks[position.x][position.y][position.z] = block;

				if (!(m_chunkFlags & NEEDS_MESHING))
					m_chunkFlags |= NEEDS_MESHING;
			}
		}
	}
}

BlockInstance Chunk::getBlockAt(phx::Vector3 position) const
{
	if (position.x < m_chunkBlocks.size())
	{
		if (position.y < m_chunkBlocks[position.x].size())
		{
			if (position.z < m_chunkBlocks[position.z].size())
			{
				return m_chunkBlocks[position.x][position.y][position.z];
			}
		}
	}

	return BlockInstance("core:out_of_bounds");
}

void Chunk::setBlockAt(phx::Vector3 position, const BlockInstance& newBlock)
{
	if (position.x < m_chunkBlocks.size())
	{
		if (position.y < m_chunkBlocks[position.x].size())
		{
			if (position.z < m_chunkBlocks[position.y].size())
			{
				m_chunkBlocks[position.x][position.y][position.z] = newBlock;

				if (!(m_chunkFlags & NEEDS_MESHING))
					m_chunkFlags |= NEEDS_MESHING;
			}
		}
	}
}

void Chunk::bufferData()
{
	if (m_blockMesh->chunkVertices.size() == 0)
		return;

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

	if (m_chunkFlags & NEEDS_MESHING)
	{
		if ((*counter) == 0)
			return;
		LDEBUG("BUILDING MESH!");
		buildMesh();
		(*counter)--;
	}

	m_textureArray->bind(10);
	m_vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, m_vertInChunk);
	m_textureArray->unbind();
	m_vao->unbind();
}