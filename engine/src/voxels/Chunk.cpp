#include "engine/voxels/Chunk.hpp"
#include <cstring>

using namespace phx::voxels;
using namespace phx;

static const Vector2 CubeUV[] = {
	// front
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),

	// back
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),

	// left
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),

	// right
	Vector2(1.f, 0.f),
	Vector2(1.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 1.f),
	Vector2(0.f, 0.f),
	Vector2(1.f, 0.f),

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
	Vector2(0.f, 1.f)
};

static const Vector3 CubeEmpty[] = {
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f),
	Vector3(0.f), Vector3(0.f), Vector3(0.f)
};

static const Vector3 CubeVerts[] = {
	// front
	Vector3(-1.f,-1.f,-1.f),
	Vector3(1.f,-1.f,-1.f),
	Vector3(1.f,1.f,-1.f),
	Vector3(1.f,1.f,-1.f),
	Vector3(-1.f,1.f,-1.f),
	Vector3(-1.f,-1.f,-1.f),

	// back
	Vector3(-1.f,-1.f,1.f),
	Vector3(1.f,-1.f,1.f),
	Vector3(1.f, 1.f,1.f),
	Vector3(1.f, 1.f,1.f),
	Vector3(-1.f, 1.f,1.f),
	Vector3(-1.f, -1.f,1.f),

	// left
	Vector3(-1.f, 1.f,1.f),
	Vector3(-1.f, 1.f,-1.f),
	Vector3(-1.f, -1.f,-1.f),
	Vector3(-1.f, -1.f,-1.f),
	Vector3(-1.f, -1.f,1.f),
	Vector3(-1.f, 1.f,1.f),

	// right
	Vector3(1.f, 1.f,1.f),
	Vector3(1.f, 1.f,-1.f),
	Vector3(1.f, -1.f,-1.f),
	Vector3(1.f, -1.f,-1.f),
	Vector3(1.f, -1.f,1.f),
	Vector3(1.f, 1.f,1.f),

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

ChunkMesh::ChunkMesh()
{
	m_blocks	= new Mesh();
	m_objects	= new Mesh();
	m_water		= new Mesh();
}

void ChunkMesh::addBlockFace(BlockFace face, int memOffset, int x, int y, int z)
{
	int bytesInFace = 6 * sizeof(Vector3);
	int memOffsetOffest = static_cast<int>(face) * 6;

	std::memcpy(m_blocks->chunkVertices.data() + memOffset + memOffsetOffest,	// Position in memory to copy to. So... original memory location + memory offset for that block + memory offset for that face.
				CubeVerts + memOffsetOffest,									// Data to copy, PLUS, the memory offset, so the correct portion of the block is copied.
				bytesInFace														// Size of Data to copy.
	);

	// Set block positions in world space
	for (int q = memOffset + memOffsetOffest; q < memOffset + memOffsetOffest + 6; q++)
	{
		m_blocks->chunkVertices[q].x += (x * 2) + (m_chunkPos.x * 2); // Multiply by 2, as that is the size of the actual cube, indicated by the cube vertices.
		m_blocks->chunkVertices[q].y += (y * 2) + (m_chunkPos.y * 2);
		m_blocks->chunkVertices[q].z += (z * 2) + (m_chunkPos.z * 2);
	}
}

void phx::voxels::ChunkMesh::setMeshPos(Vector3& chunkPos) 
{
	m_chunkPos = chunkPos;
}

Mesh* phx::voxels::ChunkMesh::getBlocksMesh()
{
	return m_blocks;
}

Mesh* phx::voxels::ChunkMesh::getObjectsMesh()
{
	return m_objects;
}

Mesh* phx::voxels::ChunkMesh::getWaterMesh()
{
	return m_water;
}

Chunk::Chunk(Vector3 chunkPos, unsigned int chunkSize, Block* defaultBlock)
{
	m_defaultBlock = defaultBlock;
	
	m_chunkData = new ChunkData();
	m_chunkData->chunkSize = chunkSize;
	m_chunkData->chunkPos = chunkPos;

	m_mesh = new ChunkMesh();
	m_mesh->setMeshPos(chunkPos);

	unsigned int sizeCubed = chunkSize * chunkSize * chunkSize;
	m_vertInChunk = sizeCubed * 36;
	m_uvInChunk = sizeCubed * 36;

	m_mesh->getBlocksMesh()->chunkVertices.resize(m_vertInChunk);
	m_mesh->getBlocksMesh()->chunkUVs.resize(m_uvInChunk);
}

void Chunk::populateData()
{
	// Set whole array to have, for example, 16 elements inside the vector.
	m_chunkData->chunkBlocks.resize(m_chunkData->chunkSize);

	for (unsigned int x = 0; x < m_chunkData->chunkBlocks.size(); x++)
	{
		// Set each X index (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][0] to m_chunkBlocks[x][15]
		m_chunkData->chunkBlocks[x].resize(m_chunkData->chunkSize);
		for (unsigned int y = 0; y < m_chunkData->chunkBlocks.size(); y++)
		{
			// Set the Y (first vector part, of the trio) to have, for example, 16 parts. So you can have m_chunkBlocks[x][y][0] to m_chunkBlocks[x][y][15]
			m_chunkData->chunkBlocks[x][y].resize(m_chunkData->chunkSize);
			for (unsigned int z = 0; z < m_chunkData->chunkBlocks.size(); z++)
			{
				// Set the Z (first vector part, of the trio) to have the actual value of the blocks data. So, you can have m_chunkBlocks[x][y][z] = BlockType::SOLID
				if (z % 4 != 0)
					m_chunkData->chunkBlocks[x][y][z] = m_defaultBlock;
				else
					m_chunkData->chunkBlocks[x][y][z] = new Block(BlockLibrary::getBlockByID("core:air"));
			}
		}
	}
}

void Chunk::buildMesh()
{
	for (unsigned int z = 0; z < m_chunkData->chunkSize; z++)
	{
		for (unsigned int y = 0; y < m_chunkData->chunkSize; y++)
		{
			for (unsigned int x = 0; x < m_chunkData->chunkSize; x++)
			{
				if (m_chunkData->chunkBlocks[x][y][z]->getBlockType() == BlockType::GAS)
					continue;

				int memOffset = (x * 36) + (m_chunkData->chunkSize * ((y * 36) + m_chunkData->chunkSize * (z * 36)));

				std::memcpy(m_mesh->getBlocksMesh()->chunkVertices.data() + memOffset, CubeEmpty, sizeof(CubeVerts));
				std::memcpy(m_mesh->getBlocksMesh()->chunkUVs.data() + memOffset, CubeUV, sizeof(CubeUV));

				if (x == 0 || m_chunkData->chunkBlocks[x - 1][y][z]->getBlockType() != BlockType::SOLID)
					m_mesh->addBlockFace(BlockFace::RIGHT, memOffset, x, y, z);
				if (x == m_chunkData->chunkSize - 1 || m_chunkData->chunkBlocks[x + 1][y][z]->getBlockType() != BlockType::SOLID)
					m_mesh->addBlockFace(BlockFace::LEFT, memOffset, x, y, z);

				if (y == 0 || m_chunkData->chunkBlocks[x][y - 1][z]->getBlockType() != BlockType::SOLID)
					m_mesh->addBlockFace(BlockFace::BOTTOM, memOffset, x, y, z);
				if (y == m_chunkData->chunkSize - 1 || m_chunkData->chunkBlocks[x][y + 1][z]->getBlockType() != BlockType::SOLID)
					m_mesh->addBlockFace(BlockFace::TOP, memOffset, x, y, z);

				if (z == 0 || m_chunkData->chunkBlocks[x][y][z - 1]->getBlockType() != BlockType::SOLID)
					m_mesh->addBlockFace(BlockFace::FRONT, memOffset, x, y, z);
				if (z == m_chunkData->chunkSize - 1 || m_chunkData->chunkBlocks[x][y][z + 1]->getBlockType() != BlockType::SOLID)
					m_mesh->addBlockFace(BlockFace::BACK, memOffset, x, y, z);
			}
		}
	}
}

ChunkMesh * phx::voxels::Chunk::getChunkMesh()
{
	return m_mesh;
}

ChunkRenderer::ChunkRenderer()
{
	m_vao = new gfx::gl::VertexArray();

	m_uvbo = new gfx::gl::VertexBuffer(gfx::gl::BufferTarget::ARRAY_BUFFER, gfx::gl::BufferUsage::DYNAMIC_DRAW);
	m_vbo = new gfx::gl::VertexBuffer(gfx::gl::BufferTarget::ARRAY_BUFFER, gfx::gl::BufferUsage::DYNAMIC_DRAW);
}

void ChunkRenderer::attachChunk(Chunk* chunkPointer)
{
	m_chunks.push_back(chunkPointer);
}

void ChunkRenderer::bufferData()
{
	if (m_chunks[0]->getChunkMesh()->getBlocksMesh()->chunkVertices.size() == 0)
		return;


	if (m_vao == nullptr)
		m_vao = new gfx::gl::VertexArray();	

	m_vao->bind();
	
	if (m_vbo == nullptr)
		m_vbo = new gfx::gl::VertexBuffer(gfx::gl::BufferTarget::ARRAY_BUFFER, gfx::gl::BufferUsage::DYNAMIC_DRAW);
	
	if (m_uvbo == nullptr)
		m_uvbo = new gfx::gl::VertexBuffer(gfx::gl::BufferTarget::ARRAY_BUFFER, gfx::gl::BufferUsage::DYNAMIC_DRAW);

	auto blockMesh = m_chunks[0]->getChunkMesh()->getBlocksMesh();
	m_vbo->bind();
	m_vbo->setData(static_cast<void*>(blockMesh->chunkVertices.data()), sizeof(blockMesh->chunkVertices[0]) * blockMesh->chunkVertices.size());	
	
	gfx::gl::VertexAttrib test(0, 3, 3, 0, gfx::gl::GLType::FLOAT);
	test.enable();

	m_uvbo->bind();
	m_uvbo->setData(static_cast<void*>(blockMesh->chunkUVs.data()), sizeof(blockMesh->chunkUVs[0]) * blockMesh->chunkUVs.size());

	gfx::gl::VertexAttrib test2(1, 2, 2, 0, gfx::gl::GLType::FLOAT);
	test2.enable();
}

void ChunkRenderer::render()
{
	m_vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 6 * 16 * 16 * 16);
	m_vao->unbind();
}