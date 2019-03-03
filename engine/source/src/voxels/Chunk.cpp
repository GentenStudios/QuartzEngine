// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#include <quartz/core/QuartzPCH.hpp>
#include <quartz/voxels/Chunk.hpp>

#include <quartz/core/graphics/API/BufferLayout.hpp>
#include <quartz/voxels/terrain/PerlinNoise.hpp>
#include "quartz/core/graphics/API/gl/GLCommon.hpp"

using namespace qz::voxels;
using namespace qz;

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

const int ACTUAL_CUBE_SIZE = 2;
const int NUM_FACES_IN_CUBE = 6;
const int NUM_VERTS_IN_FACE = 6;

struct ChunkVert3D
{
	qz::Vector3 verts;
	qz::Vector2 uvs;

	int texLayer;

	ChunkVert3D(const qz::Vector3& vertices, const qz::Vector2& UVs, const int textureLayer) :
		verts(vertices), uvs(UVs), texLayer(textureLayer)
	{}
};

void Mesh::reset()
{
	vertices.clear();
	vertices.shrink_to_fit();

	normals.clear();
	normals.shrink_to_fit();

	uvs.clear();
	uvs.shrink_to_fit();

	texLayers.clear();
	uvs.shrink_to_fit();
}

void Mesh::update(const Mesh& other)
{
	vertices = other.vertices;
	normals = other.normals;
	uvs = other.uvs;
	texLayers = other.texLayers;
}

std::size_t Mesh::triangleCount() const
{
	return vertices.size() / 3;
}

ChunkMesh::ChunkMesh(const ChunkMesh& other)
{
	m_blockMesh = other.m_blockMesh;
	m_objectMesh = other.m_objectMesh;
	m_waterMesh = other.m_waterMesh;
}

ChunkMesh& ChunkMesh::operator=(const ChunkMesh& other) = default;

ChunkMesh::ChunkMesh(ChunkMesh&& other)
{
	m_blockMesh = std::move(other.m_blockMesh);
	m_objectMesh = std::move(other.m_objectMesh);
	m_waterMesh = std::move(other.m_waterMesh);
}

ChunkMesh& ChunkMesh::operator=(ChunkMesh&& other)
{
	m_blockMesh = std::move(other.m_blockMesh);
	m_objectMesh = std::move(other.m_objectMesh);
	m_waterMesh = std::move(other.m_waterMesh);

	return *this;
}

void ChunkMesh::add(const BlockInstance& block, BlockFace face, qz::Vector3 chunkPos, qz::Vector3 blockPos, Chunk* chunk)
{
	if (block.getBlockType() == BlockType::SOLID)
	{
		ChunkRenderer& renderer = chunk->getBlockRenderer();
		
		int texLayer = -1;

		auto& blockTexList = block.getBlockTextures();

		if (static_cast<std::size_t>(face) < blockTexList.size())
		{
			renderer.reserveTexture(blockTexList[static_cast<int>(face)]);
			texLayer = renderer.getTexLayer(blockTexList[static_cast<int>(face)]);
		}

		for (int i = 0; i < NUM_VERTS_IN_FACE; ++i)
		{
			qz::Vector3 blockVertices = CUBE_VERTS[(static_cast<int>(face) * NUM_FACES_IN_CUBE) + i];
			blockVertices.x += (blockPos.x * ACTUAL_CUBE_SIZE) + (chunkPos.x * ACTUAL_CUBE_SIZE); // Multiply by 2, as that is the size of the actual cube edges, indicated by the cube vertices.
			blockVertices.y += (blockPos.y * ACTUAL_CUBE_SIZE) + (chunkPos.y * ACTUAL_CUBE_SIZE);
			blockVertices.z += (blockPos.z * ACTUAL_CUBE_SIZE) + (chunkPos.z * ACTUAL_CUBE_SIZE);

			qz::Vector2 cubeUVs = CUBE_UV[(static_cast<int>(face) * NUM_FACES_IN_CUBE) + i];

			m_blockMesh.vertices.push_back(blockVertices);
			m_blockMesh.uvs.push_back(cubeUVs);
			m_blockMesh.texLayers.push_back(texLayer);
		}
	}
}

const Mesh& ChunkMesh::getBlockMesh() const
{
	return m_blockMesh;
}

const Mesh& ChunkMesh::getObjectMesh() const
{
	return m_objectMesh;
}

const Mesh& ChunkMesh::getWaterMesh() const
{
	return m_waterMesh;
}

void ChunkMesh::resetAll()
{
	m_blockMesh.reset();
	m_objectMesh.reset();
	m_waterMesh.reset();
}

ChunkRenderer::ChunkRenderer() {}
ChunkRenderer::~ChunkRenderer() {}

ChunkRenderer::ChunkRenderer(const ChunkRenderer& other)
{
	m_mesh = other.m_mesh;
}

ChunkRenderer& ChunkRenderer::operator=(const ChunkRenderer& other)
{
	m_mesh = other.m_mesh;

	m_stateManager = nullptr;
	m_buffer = nullptr;
	m_textureArray = nullptr;

	return *this;
}

ChunkRenderer::ChunkRenderer(ChunkRenderer&& other)
{
	m_mesh = std::move(other.m_mesh);

	m_stateManager = nullptr;
	m_buffer = nullptr;

	std::swap(m_textureArray, other.m_textureArray);
}

ChunkRenderer& ChunkRenderer::operator=(ChunkRenderer&& other)
{
	m_mesh = std::move(other.m_mesh);

	std::swap(m_textureArray, other.m_textureArray);

	return *this;
}

void ChunkRenderer::resetMesh()
{
	m_mesh.reset();
}

void ChunkRenderer::updateMesh(const Mesh& mesh)
{
	m_mesh.update(mesh);
}

void ChunkRenderer::reserveTexture(const std::string& path)
{
	if (m_texReservations.find(path) == m_texReservations.end())
	{
		m_texReservations.emplace(path, m_currentLayer);
		m_currentLayer++;
	}
}

int ChunkRenderer::getTexLayer(const std::string& path)
{
	const auto it = m_texReservations.find(path);

	if (it == m_texReservations.end())
	{
		return m_textureArray->getTexLayer(path);
	}

	return it->second;
}

void ChunkRenderer::loadTextures()
{
	if (m_textureArray == nullptr)
		m_textureArray = gfx::api::ITextureArray::generateTextureArray();

	m_textureArray->add(m_texReservations);
}

void ChunkRenderer::bufferData()
{
	if (m_mesh.vertices.empty())
		return;

	if (m_stateManager == nullptr)
		m_stateManager = gfx::api::IStateManager::generateStateManager();

	m_stateManager->bind();

	if (m_buffer == nullptr)
		m_buffer = gfx::api::IBuffer::generateBuffer(gfx::api::BufferTarget::ARRAY_BUFFER, gfx::api::BufferUsage::DYNAMIC);

	std::vector<ChunkVert3D> temp;

	// Not doing vector::size() - 1, i >= 0; as std::size_t is a variant of an unsigned int, which does not go below 0, making it an infinitely running loop. 
	// (i mean, shit would DEFINITELY hit the ceiling first, but who even fucking cares)
	for (std::size_t i = m_mesh.vertices.size(); i > 0; i--)
	{
		temp.emplace_back(m_mesh.vertices[i - 1], m_mesh.uvs[i - 1], m_mesh.texLayers[i - 1]);
	}

	m_buffer->bind();
	m_buffer->setData(sizeof(ChunkVert3D) * temp.size(), static_cast<void*>(temp.data()));

	m_stateManager->attachBuffer(m_buffer);

	gfx::api::BufferLayout bufferLayout;

	bufferLayout.registerAttribute(0, qz::gfx::DataType::FLOAT, 3, sizeof(ChunkVert3D), offsetof(ChunkVert3D, verts), false);
	bufferLayout.registerAttribute(1, qz::gfx::DataType::FLOAT, 2, sizeof(ChunkVert3D), offsetof(ChunkVert3D, uvs), false);
	bufferLayout.registerAttribute(2, qz::gfx::DataType::FLOAT, 1, sizeof(ChunkVert3D), offsetof(ChunkVert3D, texLayer), false);

	m_stateManager->attachBufferLayout(bufferLayout);

	m_stateManager->unbind();

	// bufferData() is usually called just before a render call, meaning that if the textureArray is a nullptr, then things will go south pretty fucking fast.
	if (m_textureArray == nullptr)
		m_textureArray = gfx::api::ITextureArray::generateTextureArray();
}

void ChunkRenderer::render() const
{
	if (m_mesh.vertices.empty())
		return;

	m_textureArray->bind(10);
	m_stateManager->bind();
	GLCheck(glDrawArrays(GL_TRIANGLES, 0, m_mesh.vertices.size()));
}

std::size_t ChunkRenderer::getTrianglesCount() const
{
	return m_mesh.triangleCount();
}

Chunk::Chunk(const Chunk& other) : m_chunkFlags(NEEDS_MESHING)
{
	m_chunkPos = other.m_chunkPos;
	m_chunkSize = other.m_chunkSize;

	m_mesh = other.m_mesh;

	m_blockRenderer = ChunkRenderer();
	m_objectRenderer = ChunkRenderer();
	m_waterRenderer = ChunkRenderer();

	m_defaultBlockID = other.m_defaultBlockID;
	m_chunkBlocks = other.m_chunkBlocks;
}

Chunk& Chunk::operator=(const Chunk& other)
{
	if (&other == this)
		return *this;

	m_chunkPos = other.m_chunkPos;
	m_chunkSize = other.m_chunkSize;

	m_mesh = other.m_mesh;

	m_blockRenderer = ChunkRenderer();
	m_objectRenderer = ChunkRenderer();
	m_waterRenderer = ChunkRenderer();

	m_defaultBlockID = other.m_defaultBlockID;
	m_chunkBlocks = other.m_chunkBlocks;

	return *this;
}

Chunk::Chunk(Chunk&& other)
{
	m_chunkPos = other.m_chunkPos;
	m_chunkSize = other.m_chunkSize;

	m_mesh = std::move(other.m_mesh);

	m_blockRenderer = std::move(other.m_blockRenderer);
	m_objectRenderer = std::move(other.m_objectRenderer);
	m_waterRenderer = std::move(other.m_waterRenderer);

	m_chunkFlags = NEEDS_MESHING;

	m_defaultBlockID = std::move(other.m_defaultBlockID);
	m_chunkBlocks = std::move(other.m_chunkBlocks);
}

Chunk& Chunk::operator=(Chunk&& other)
{
	m_chunkPos = other.m_chunkPos;
	m_chunkSize = other.m_chunkSize;

	m_mesh = std::move(other.m_mesh);

	m_blockRenderer = std::move(other.m_blockRenderer);
	m_objectRenderer = std::move(other.m_objectRenderer);
	m_waterRenderer = std::move(other.m_waterRenderer);

	m_chunkFlags = NEEDS_MESHING;

	m_defaultBlockID = std::move(other.m_defaultBlockID);

	m_chunkBlocks = std::move(other.m_chunkBlocks);

	return *this;
}

Chunk::Chunk(qz::Vector3 chunkPos, int chunkSize, const std::string& defaultBlockID)
{
	m_chunkPos = chunkPos;
	m_chunkSize = chunkSize;
	m_defaultBlockID = defaultBlockID;

	m_chunkFlags = 0;
}

void Chunk::populateData(unsigned int seed)
{
	for (std::size_t i = 0; i < m_chunkSize * m_chunkSize * m_chunkSize; ++i)
		m_chunkBlocks.emplace_back(m_defaultBlockID);

	PerlinNoise* terrainGenerator = new PerlinNoise(seed);
	terrainGenerator->generateFor(m_chunkBlocks, m_chunkPos, m_chunkSize);
	delete terrainGenerator;

	if (!(m_chunkFlags & NEEDS_MESHING))
		m_chunkFlags |= NEEDS_MESHING;
}

void Chunk::buildMesh()
{
	m_mesh.resetAll();
	
	for (std::size_t j = m_chunkSize * m_chunkSize * m_chunkSize; j > 0; --j)
	{
		std::size_t i = j - 1;
		BlockInstance& block = m_chunkBlocks[i];

		if (block.getBlockType() == BlockType::GAS)
			continue;

		const int x = i % m_chunkSize;
		const int y = (i / m_chunkSize) % m_chunkSize;
		const int z = i / (m_chunkSize * m_chunkSize);

		if (x == 0 || m_chunkBlocks[getVectorIndex(x - 1, y, z)].getBlockType() != BlockType::SOLID)
			m_mesh.add(block, BlockFace::RIGHT, m_chunkPos, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, this);
		if (x == m_chunkSize - 1 || m_chunkBlocks[getVectorIndex(x + 1, y, z)].getBlockType() != BlockType::SOLID)
			m_mesh.add(block, BlockFace::LEFT, m_chunkPos, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, this);

		if (y == 0 || m_chunkBlocks[getVectorIndex(x, y - 1, z)].getBlockType() != BlockType::SOLID)
			m_mesh.add(block, BlockFace::BOTTOM, m_chunkPos, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, this);
		if (y == m_chunkSize - 1 || m_chunkBlocks[getVectorIndex(x, y + 1, z)].getBlockType() != BlockType::SOLID)
			m_mesh.add(block, BlockFace::TOP, m_chunkPos, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, this);

		if (z == 0 || m_chunkBlocks[getVectorIndex(x, y, z - 1)].getBlockType() != BlockType::SOLID)
			m_mesh.add(block, BlockFace::FRONT, m_chunkPos, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, this);
		if (z == m_chunkSize - 1 || m_chunkBlocks[getVectorIndex(x, y, z + 1)].getBlockType() != BlockType::SOLID)
			m_mesh.add(block, BlockFace::BACK, m_chunkPos, { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }, this);

	}

	if (!(m_chunkFlags & BLOCKS_NEED_BUFFERING))
		m_chunkFlags |= BLOCKS_NEED_BUFFERING;

	if (!(m_chunkFlags & BLOCKS_NEED_TEXTURING))
		m_chunkFlags |= BLOCKS_NEED_TEXTURING;

	m_chunkFlags &= ~NEEDS_MESHING;

	m_blockRenderer.resetMesh();
	m_blockRenderer.updateMesh(m_mesh.getBlockMesh());
}

const ChunkMesh& Chunk::getChunkMesh() const
{
	return m_mesh;
}

const Vector3& Chunk::getChunkPos() const
{
	return m_chunkPos;
}

void Chunk::breakBlockAt(qz::Vector3 position, const BlockInstance& block)
{
	if (position.x < m_chunkSize)
	{
		if (position.y < m_chunkSize)
		{
			if (position.z < m_chunkSize)
			{
				BlockInstance& orig = m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))];

				auto& breakCallback = BlockLibrary::get()->requestBlock(orig.getBlockID()).getBreakCallback();
				if (breakCallback != nullptr)
					breakCallback();

				orig = block;

				if (!(m_chunkFlags & NEEDS_MESHING))
					m_chunkFlags |= NEEDS_MESHING;
			}
		}
	}
}

void Chunk::placeBlockAt(qz::Vector3 position, const BlockInstance& block)
{
	if (position.x < m_chunkSize)
	{
		if (position.y < m_chunkSize)
		{
			if (position.z < m_chunkSize)
			{
				auto& placeCallback = BlockLibrary::get()->requestBlock(block.getBlockID()).getPlaceCallback();
				if (placeCallback != nullptr)
					placeCallback();

				m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))] = block;

				if (!(m_chunkFlags & NEEDS_MESHING))
					m_chunkFlags |= NEEDS_MESHING;
			}
		}
	}
}

BlockInstance Chunk::getBlockAt(qz::Vector3 position) const
{
	if (position.x < m_chunkSize)
	{
		if (position.y < m_chunkSize)
		{
			if (position.z < m_chunkSize)
			{
				return m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))];
			}
		}
	}

	return BlockInstance("core:out_of_bounds");
}

void Chunk::setBlockAt(qz::Vector3 position, const BlockInstance& newBlock)
{
	if (position.x < m_chunkSize)
	{
		if (position.y < m_chunkSize)
		{
			if (position.z < m_chunkSize)
			{
				m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))] = newBlock;

				if (!(m_chunkFlags & NEEDS_MESHING))
					m_chunkFlags |= NEEDS_MESHING;
			}
		}
	}
}

ChunkRenderer& Chunk::getBlockRenderer()
{
	return m_blockRenderer;
}

ChunkRenderer& Chunk::getObjectRenderer()
{
	return m_objectRenderer;
}

ChunkRenderer& Chunk::getWaterRenderer()
{
	return m_waterRenderer;
}

void Chunk::renderBlocks(int* counter)
{
	if (m_chunkFlags & BLOCKS_NEED_BUFFERING)
	{
		if (*counter > 0)
			(*counter)--;
		else
			return;

		m_blockRenderer.bufferData();
		m_chunkFlags &= ~BLOCKS_NEED_BUFFERING;
	}

	if (m_chunkFlags & BLOCKS_NEED_TEXTURING)
	{
		if (*counter > 0)
			(*counter)--;
		else
			return;

		m_blockRenderer.loadTextures();
		m_chunkFlags &= ~BLOCKS_NEED_TEXTURING;
	}

	m_blockRenderer.render();

	if (m_chunkFlags & NEEDS_MESHING)
	{
		if (*counter > 0)
			(*counter)--;
		else
			return;

		buildMesh();
		m_chunkFlags &= ~NEEDS_MESHING;
	}
}

void Chunk::renderObjects(int* counter)
{
	// TODO: Write function for rendering objects. (TO BE DONE ONCE WE ACTUALLY HAVE OBJECTS)
}

void Chunk::renderWater(int* counter)
{
	// TODO: Write function for rendering water. (TO BE DONE ONCE WE ACTUALLY HAVE WATER)
}

