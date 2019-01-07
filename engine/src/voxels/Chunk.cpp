#include <engine/voxels/Chunk.hpp>

#include <engine/core/graphics/gl/VertexAttrib.hpp>
#include <engine/voxels/terrain/PerlinNoise.hpp>

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

const int ACTUAL_CUBE_SIZE = 2;
const int NUM_FACES_IN_CUBE = 6;
const int NUM_VERTS_IN_FACE = 6;

struct ChunkVert3D
{
	phx::Vector3 verts;
	phx::Vector2 uvs;

	int texLayer;

	ChunkVert3D(const phx::Vector3& vertices, const phx::Vector2& UVs, const int textureLayer) :
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

void ChunkMesh::add(const BlockInstance& block, BlockFace face, phx::Vector3 chunkPos, phx::Vector3 blockPos, Chunk* chunk)
{
	if (block.getBlockType() == BlockType::SOLID)
	{
		ChunkRenderer& renderer = chunk->getBlockRenderer();
		
		int texLayer = -1;

		auto& blockTexList = block.getBlockTextures();

		if (static_cast<std::size_t>(face) < blockTexList.size())
		{
			gfx::gl::TextureArray* texArray = renderer.getTextureArray();
			texArray->reserve(blockTexList[static_cast<int>(face)]);
			texLayer = texArray->getTexLayer(blockTexList[static_cast<int>(face)]);
		}

		for (int i = 0; i < NUM_VERTS_IN_FACE; ++i)
		{
			phx::Vector3 blockVertices = CUBE_VERTS[(static_cast<int>(face) * NUM_FACES_IN_CUBE) + i];
			blockVertices.x += (blockPos.x * ACTUAL_CUBE_SIZE) + (chunkPos.x * ACTUAL_CUBE_SIZE); // Multiply by 2, as that is the size of the actual cube edges, indicated by the cube vertices.
			blockVertices.y += (blockPos.y * ACTUAL_CUBE_SIZE) + (chunkPos.y * ACTUAL_CUBE_SIZE);
			blockVertices.z += (blockPos.z * ACTUAL_CUBE_SIZE) + (chunkPos.z * ACTUAL_CUBE_SIZE);

			phx::Vector2 cubeUVs = CUBE_UV[(static_cast<int>(face) * NUM_FACES_IN_CUBE) + i];

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

ChunkRenderer::ChunkRenderer() :
	m_vao(nullptr), m_vbo(nullptr)
{
	m_textureArray = new gfx::gl::TextureArray();
}

ChunkRenderer::~ChunkRenderer()
{
	delete m_vao;
	delete m_vbo;
}

void ChunkRenderer::resetMesh()
{
	m_mesh.reset();
}

void ChunkRenderer::updateMesh(const Mesh& mesh)
{
	m_mesh.update(mesh);
}

gfx::gl::TextureArray* ChunkRenderer::getTextureArray() const
{
	return m_textureArray;
}

void ChunkRenderer::bufferData()
{
	if (m_mesh.vertices.empty())
		return;

	if (m_vao == nullptr)
		m_vao = new gfx::gl::VertexArray();

	m_vao->bind();

	if (m_vbo == nullptr)
		m_vbo = new gfx::gl::VertexBuffer(gfx::gl::BufferTarget::ARRAY_BUFFER, gfx::gl::BufferUsage::DYNAMIC_DRAW);

	std::vector<ChunkVert3D> temp;

	// Not doing vector::size() - 1, i >= 0; as std::size_t is a variant of an unsigned int, which does not go below 0, making it an infinitely running loop. 
	// (i mean, shit would DEFINITELY hit the ceiling first, but who even fucking cares)
	for (std::size_t i = m_mesh.vertices.size(); i > 0; i--)
	{
		temp.emplace_back(m_mesh.vertices[i - 1], m_mesh.uvs[i - 1], m_mesh.texLayers[i - 1]);
	}

	m_vbo->bind();
	m_vbo->setData(static_cast<void*>(temp.data()), sizeof(ChunkVert3D) * temp.size());

	gfx::gl::VertexAttrib vertAttrib	= gfx::gl::VertexAttrib(0, 3, sizeof(ChunkVert3D), offsetof(ChunkVert3D, verts),	gfx::gl::GLType::FLOAT);
	gfx::gl::VertexAttrib uvAttrib		= gfx::gl::VertexAttrib(1, 2, sizeof(ChunkVert3D), offsetof(ChunkVert3D, uvs),		gfx::gl::GLType::FLOAT);
	gfx::gl::VertexAttrib layerAttrib	= gfx::gl::VertexAttrib(2, 1, sizeof(ChunkVert3D), offsetof(ChunkVert3D, texLayer),	gfx::gl::GLType::FLOAT);

	vertAttrib.enable();
	uvAttrib.enable();
	layerAttrib.enable();

	m_vao->unbind();
}

void ChunkRenderer::render() const
{
	if (m_mesh.vertices.empty())
		return;

	m_textureArray->bind(10);
	m_vao->bind();
	GLCheck(glDrawArrays(GL_TRIANGLES, 0, m_mesh.vertices.size()));
	m_textureArray->unbind();
	m_vao->unbind();
}

std::size_t ChunkRenderer::getTrianglesCount() const
{
	return m_mesh.triangleCount();
}

Chunk::Chunk(phx::Vector3 chunkPos, unsigned int chunkSize, const std::string& defaultBlockID)
{
	m_chunkPos = chunkPos;
	m_chunkSize = chunkSize;
	m_defaultBlockID = defaultBlockID;

	m_chunkFlags = NEEDS_MESHING;
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

	for (std::size_t i = 0; i < m_chunkSize * m_chunkSize * m_chunkSize; ++i)
	{
		BlockInstance& block = m_chunkBlocks[i];

		if (block.getBlockType() == BlockType::GAS)
			continue;

		std::size_t x = i % m_chunkSize;
		std::size_t y = (i / m_chunkSize) % m_chunkSize;
		std::size_t z = i / (m_chunkSize * m_chunkSize);

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

void Chunk::breakBlockAt(phx::Vector3 position, const BlockInstance& block)
{
	position.floor();
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

				m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))] = block;

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
				return m_chunkBlocks[getVectorIndex(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z))];
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

		m_blockRenderer.getTextureArray()->resolveReservations();
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
