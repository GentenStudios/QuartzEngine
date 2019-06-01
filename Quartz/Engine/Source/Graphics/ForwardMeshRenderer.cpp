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
using namespace qz;

//#todo (bwilks): this shouldn't always be hardcoded.
static const char* SHADER_FILEPATH = "assets/shaders/basic.shader";

void ForwardMeshRenderer::create()
{
	// #todo (bwilks): currently these are not required as the Matrix4x4 default
	// constructor will init to identity (may change that soon tho)
	m_viewMatrix.setIdentity();
	m_projectionMatrix.setIdentity();

	rhi::InputLayout layout = {
		{ rhi::VertexElementType::Vec3f, 0, 0, 0,                 false },
		{ rhi::VertexElementType::Vec2f, 0, 1, 3 * sizeof(float), false }
	};

	m_shader = m_renderDevice->createShaderPipeline(SHADER_FILEPATH, layout);
	m_renderDevice->setShaderPipeline(m_shader);

	m_viewMatrixUniform = m_renderDevice->createUniform(m_shader, "u_view", rhi::UniformType::MAT4);
	m_projectionMatrixUniform = m_renderDevice->createUniform(m_shader, "u_projection", rhi::UniformType::MAT4);

	rhi::UniformHandle textureSamplerUniform = m_renderDevice->createUniform(m_shader, "u_texture", rhi::UniformType::SAMPLER);
	int textureSampler0 = 0;
	m_renderDevice->setUniformValue(textureSamplerUniform, &textureSampler0, 1);
}

void ForwardMeshRenderer::destroy()
{
	for(MeshRenderData& mesh : m_meshes)
	{
		m_renderDevice->freeVertexBuffer(mesh.vertexBuffer);
	}

	m_renderDevice->freeUniform(m_viewMatrixUniform);
	m_renderDevice->freeUniform(m_projectionMatrixUniform);
	m_renderDevice->freeShaderPipeline(m_shader);
}

ForwardMeshRenderer::ForwardMeshRenderer(rhi::IRenderDevice* renderDevice)
	: m_renderDevice(renderDevice)
{}

void ForwardMeshRenderer::setViewMatrix(const Matrix4x4& view)
{
	m_viewMatrix = view;
	m_renderDevice->setUniformValue(m_viewMatrixUniform, &m_viewMatrix, 1);
}

void ForwardMeshRenderer::setProjectionMatrix(const Matrix4x4& projection)
{
	m_projectionMatrix = projection;
	m_renderDevice->setUniformValue(m_projectionMatrixUniform, &m_projectionMatrix, 1);
}

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
		const PhongMaterial& material = mesh.mesh->getMaterial();
		m_renderDevice->setTexture(material.texture, 0); // #todo (bwilks): CAN'T BIND ALL TO SLOT 0
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
