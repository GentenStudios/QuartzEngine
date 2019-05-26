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

#include <Quartz/Graphics/ForwardMeshRenderer.hpp>
#include <Quartz/Utilities/Logger.hpp>

#include <numeric>

using namespace qz::gfx;

ForwardMeshRenderer::ForwardMeshRenderer(rhi::IRenderDevice* renderDevice)
	: m_renderDevice(renderDevice)
{}

void ForwardMeshRenderer::submitMesh(Mesh* mesh)
{
	MeshRenderData renderData;
	renderData.mesh = mesh;

	const std::vector<Vertex3D>& vertices = mesh->getVertices();
	float* verticesPtr = reinterpret_cast<float*>(const_cast<Vertex3D*>(vertices.data()));
	const std::size_t sizebytes = vertices.size() * sizeof(Vertex3D);

	rhi::VertexBufferHandle buffer = m_renderDevice->createVertexBuffer();
	m_renderDevice->setBufferData(buffer, verticesPtr, sizebytes);

	renderData.vertexBuffer = buffer;
	m_meshes.push_back(renderData);
}

void ForwardMeshRenderer::render()
{
	for(MeshRenderData& mesh : m_meshes)
	{
		m_renderDevice->setVertexBufferStream(mesh.vertexBuffer, 0, sizeof(Vertex3D), 0);
		m_renderDevice->draw(0, mesh.mesh->getVertices().size());
	}
}

std::size_t ForwardMeshRenderer::countTotalNumVertices()
{
	return std::accumulate(m_meshes.begin(), m_meshes.end(), std::size_t(0), [](std::size_t acu, const MeshRenderData& data){
		return acu + data.mesh->getVertices().size();
	});
}
