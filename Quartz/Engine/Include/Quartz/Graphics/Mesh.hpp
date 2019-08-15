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

#include <Quartz/Math/Math.hpp>

#include <cstddef>
#include <vector>

#include <Quartz/Graphics/RHI/IRenderDevice.hpp>

namespace qz
{
	namespace gfx
	{
		/// @brief Represents a material lit by the phong lighting model.
		struct PhongMaterial
		{
			/// @brief Ambient lighting levels for this material.
			Vector3 ambient;

			/// @brief Diffuse lighting levels for this material.
			Vector3 diffuse;

			/// @brief Specular lighting levels for this material.
			Vector3 specular;

			/// @brief Level representing how "shiny" this material is.
			float   shininess;

			/// @brief Texture for this material.
			rhi::TextureHandle texture;
		};
		
		/// @brief Represents a vertex in 3D space.
		struct Vertex3D
		{
			/// @brief The position of this vertex.
			Vector3 position;

			/// @brief The UV coordinates in the texture for this vertex.
			Vector2 uv;

			/// @brief The color of this vertex.
			Vector3 color;
		};
		
		/// @brief Represents a mesh to render.
		class Mesh
		{
		private:
			/// @brief List of all the vertices for this mesh
			std::vector<Vertex3D> m_vertices;

			/// @brief The material for this mesh.
			PhongMaterial         m_material;

		public:
			/**
			 * @brief Construct a mesh with the given vertices and an undefined material.
			 * @param vertices The inital vertices of the mesh.
			 */
			Mesh(const std::vector<Vertex3D>& vertices);

			/**
			 * @brief Default construct a mesh - no vertices & an undefined material.
			 */
			Mesh();

			/**
			 * @brief Construct a mesh with no vertices and an undefined material, but reserve memory for
			 *        `vertexCapacity` vertices.
			 */
			Mesh(std::size_t vertexCapacity);

			/**
			 * @brief Return a reference to the list of vertices in this mesh.
			 * @return A constant reference to the list of mesh vertices.
			 */
			const std::vector<Vertex3D>& getVertices() const { return m_vertices; }

			/**
			 * @brief Return the material used by this mesh.
			 * @return The material of this mesh.
			 */
			const PhongMaterial& getMaterial() const { return m_material; }

			/**
			 * @brief Add a single vertex to this mesh.
			 * @param vertex The vertex to add to this mesh.
			 */
			void addVertex(const Vertex3D& vertex);

			/**
			 * @brief Set the mesh on this object. Should be set at least once, as the material is undefined otherwise.
			 * @param material The new material of the mesh.
			 */
			void setMaterial(const PhongMaterial& material);
		};
	}
}
