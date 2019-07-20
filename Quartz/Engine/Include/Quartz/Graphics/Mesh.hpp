// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <Quartz/Math/Math.hpp>

#include <cstddef>
#include <vector>

#include <Quartz/Graphics/RHI/IRenderDevice.hpp>

namespace qz
{
	namespace gfx
	{
		struct PhongMaterial
		{
			Vector3            ambient;
			Vector3            diffuse;
			Vector3            specular;
			float              shininess;
			rhi::TextureHandle texture;
		};

		struct Vertex3D
		{
			Vector3 position;
			Vector2 uv;
			Vector3 color;
		};

		class Mesh
		{
		  private:
			std::vector<Vertex3D> m_vertices;
			PhongMaterial         m_material;

		  public:
			Mesh (const std::vector<Vertex3D>& vertices);
			Mesh ();
			Mesh (std::size_t vertexCapacity);

			const std::vector<Vertex3D>& getVertices () const
			{
				return m_vertices;
			}

			const PhongMaterial& getMaterial () const { return m_material; }

			void addVertex (const Vertex3D& vertex);
			void setMaterial (const PhongMaterial& material);
		};
	} // namespace gfx
} // namespace qz
