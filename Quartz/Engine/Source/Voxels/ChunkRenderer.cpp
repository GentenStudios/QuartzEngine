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

#include <Quartz/Voxels/ChunkRenderer.hpp>
#include <Quartz/Voxels/Chunk.hpp>
#include <Quartz/Core/Utilities/Logger.hpp>

#include <cstddef>

using namespace qz::voxels;
using namespace qz;

ChunkRenderer::ChunkRenderer(const ChunkRenderer& other)
{
	m_stateManager = other.m_stateManager;
	m_buffer = other.m_buffer;
	m_textureArray = other.m_textureArray;
	m_verticesToDraw = other.m_verticesToDraw;
}

ChunkRenderer& ChunkRenderer::operator=(const ChunkRenderer& other)
{
	m_stateManager = other.m_stateManager;
	m_buffer = other.m_buffer;
	m_textureArray = other.m_textureArray;
	m_verticesToDraw = other.m_verticesToDraw;

	return *this;
}

ChunkRenderer::ChunkRenderer(ChunkRenderer&& other) noexcept
{
	m_stateManager = other.m_stateManager;
	m_buffer = other.m_buffer;
	m_textureArray = other.m_textureArray;
	m_verticesToDraw = other.m_verticesToDraw;
}

ChunkRenderer& ChunkRenderer::operator=(ChunkRenderer&& other) noexcept
{
	m_stateManager = other.m_stateManager;
	m_buffer = other.m_buffer;
	m_textureArray = other.m_textureArray;
	m_verticesToDraw = other.m_verticesToDraw;

	return *this;
}

bool ChunkRenderer::updateMesh(const ChunkMesh& mesh, int* bufferCounter)
{
	if ((*bufferCounter) < 2)
		return false;
	
	{
		--(*bufferCounter);

		m_verticesToDraw = mesh.verts.size();

		if (m_verticesToDraw == 0)
			return true;

		if (m_stateManager == nullptr)
			m_stateManager = gfx::api::IStateManager::generateStateManager();

		m_stateManager->bind();

		if (m_buffer == nullptr)
			m_buffer = gfx::api::IBuffer::generateBuffer(gfx::api::BufferTarget::ARRAY_BUFFER, gfx::api::BufferUsage::DYNAMIC);

		m_buffer->bind();
		m_buffer->setData(sizeof(ChunkVert3D) * mesh.verts.size(), static_cast<const void*>(mesh.verts.data()));

		m_stateManager->attachBuffer(m_buffer);

		gfx::api::BufferLayout bufferLayout;

		bufferLayout.registerAttribute(0, qz::gfx::DataType::FLOAT, 3, sizeof(ChunkVert3D), offsetof(ChunkVert3D, verts), false);
		bufferLayout.registerAttribute(1, qz::gfx::DataType::FLOAT, 2, sizeof(ChunkVert3D), offsetof(ChunkVert3D, uvs), false);
		bufferLayout.registerAttribute(2, qz::gfx::DataType::FLOAT, 1, sizeof(ChunkVert3D), offsetof(ChunkVert3D, texLayer), false);

		m_stateManager->attachBufferLayout(bufferLayout);

		m_stateManager->unbind();
	}

	{
		if (m_textureArray == nullptr)
			m_textureArray = gfx::api::ITextureArray::generateTextureArray();

		if (mesh.textureCache != m_textureArray->getTextureList())
		{
			--(*bufferCounter);
			m_textureArray->add(mesh.textureCache);
		}
	}

	return true;
}

void ChunkRenderer::render() const
{
	if (m_verticesToDraw == 0)
		return;

	m_textureArray->bind(10);
	m_stateManager->bind();
	m_stateManager->render(0, m_verticesToDraw);
}
