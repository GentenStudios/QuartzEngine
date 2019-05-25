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

#pragma once

#include <Quartz/Graphics/API/IStateManager.hpp>
#include <Quartz/Graphics/API/IBuffer.hpp>
#include <Quartz/Graphics/API/ITextureArray.hpp>

namespace qz
{
	namespace voxels
	{
		struct ChunkMesh;
		struct ChunkVert3D
		{
			qz::Vector3 verts;
			qz::Vector2 uvs;

			int texLayer;

			ChunkVert3D(const qz::Vector3& vertices, const qz::Vector2& UVs, const int textureLayer) :
				verts(vertices), uvs(UVs), texLayer(textureLayer)
			{}
		};

		class ChunkRenderer
		{
		public:
			ChunkRenderer() = default;
			~ChunkRenderer() = default;

			ChunkRenderer(const ChunkRenderer& other);
			ChunkRenderer& operator=(const ChunkRenderer& other);

			ChunkRenderer(ChunkRenderer&& other) noexcept;
			ChunkRenderer& operator=(ChunkRenderer&& other) noexcept;

			bool updateMesh(const ChunkMesh& mesh, int* bufferCounter);
			void render() const;

		private:
			std::size_t m_verticesToDraw = 0;

			gfx::api::GraphicsResource<gfx::api::IStateManager> m_stateManager = nullptr;
			gfx::api::GraphicsResource<gfx::api::IBuffer> m_buffer = nullptr;
			gfx::api::GraphicsResource<gfx::api::ITextureArray> m_textureArray = nullptr;
		};
	}
}
