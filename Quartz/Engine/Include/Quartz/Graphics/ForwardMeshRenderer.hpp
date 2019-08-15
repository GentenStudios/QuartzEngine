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

#include <Quartz/Graphics/Mesh.hpp>
#include <Quartz/Graphics/RHI/IRenderDevice.hpp>
#include <Quartz/Math/Matrix4x4.hpp>
#include <Quartz/Utilities/HandleAllocator.hpp>

#include <vector>

namespace qz
{
	namespace gfx
	{
		/// @brief Handle for representing GPU texture slots.
		struct TextureSlotHandle : utils::HandleBase
		{
		};

		/// @brief Renderer based of a forward rendering design.
		class ForwardMeshRenderer
		{
		private:
			/// @brief Pointer to the API specific RenderDevice, used for
			/// interacting with the
			///        platform graphics API
			rhi::IRenderDevice* m_renderDevice;

			/// @brief The shader to use for rendering.
			rhi::ShaderPipelineHandle m_shader;

			/// @brief Shader uniforms for the projection and view matrices.
			rhi::UniformHandle m_viewMatrixUniform, m_projectionMatrixUniform;

			/// @brief Handles to all the textures that can be held in texture
			/// slots at one time.
			utils::HandleAllocator<32, TextureSlotHandle>
			    m_textureSlotsAllocator;

			/// @brief Represents all the data needed to render a mesh - both
			/// internal and user-facing data.
			struct MeshRenderData
			{
				/// @brief Vertex buffer handle for this texture - handle to the
				/// GPU vertex data.
				rhi::VertexBufferHandle vertexBuffer;

				/// @brief Pointer to the user-facing mesh data.
				Mesh* mesh;

				/// @brief Texture slot that the texture used by this mesh is
				/// stored in.
				TextureSlotHandle textureSlot;
			};

			/// @brief List of all meshes to be rendered.
			std::vector<MeshRenderData> m_meshes;

			/// @brief The values of the view and projection matrices.
			Matrix4x4 m_viewMatrix, m_projectionMatrix;

			/// @brief Default texture handle (used if no texture specified)
			rhi::TextureHandle m_defaultTexture;

			/// @brief Slot for the default texture (used if no texture is
			/// specified)
			TextureSlotHandle m_defaultTextureSlot;

		public:
			/**
			 * @brief Initial constructor for the renderer. Does not initialize
			 * all state - create() also needs called.
			 */
			ForwardMeshRenderer(rhi::IRenderDevice* renderDevice);

			/**
			 * @brief Initializes the state of the renderer. Must be called
			 * before any other method is called.
			 */
			void create();

			/**
			 * @brief Destroys any resources used by the renderer - no other
			 *        method of this instance should be called after this, as
			 * the renderer cannot be assumed to be in a usable or even
			 * recoverable state. Any data associated with this object should
			 * also be assumed to be invalid.
			 */
			void destroy();

			/**
			 * @brief Submit a mesh to be rendered.
			 * @param mesh A pointer to the mesh to be rendered. Cannot be null.
			 */
			void submitMesh(Mesh* mesh);

			/*
			 * @brief Render the scene - i.e. any meshes that have been
			 * submitted with submitMesh ()
			 */
			void render();

			/*
			 * @brief Set the projection matrix to be used when rendering.
			 *        Should be set at least once before the first render()
			 * call.
			 * @param projection The new projection matrix.
			 */
			void setProjectionMatrix(const Matrix4x4& projection);

			/*
			 * @brief Set the view matrix to be used when rendering.
			 *        Should be set at least once before the first render()
			 * call.
			 * @param view The new view matrix.
			 */
			void setViewMatrix(const Matrix4x4& view);

			/*
			 * @brief Return the current projection matrix. If
			 * setProjectionMatrix has not been called then this return value is
			 * undefined.
			 * @return The current projection matrix. Undefined if not
			 * explicitly set.
			 */
			Matrix4x4 getProjectionMatrix() const { return m_projectionMatrix; }

			/*
			 * @brief Get the current view matrix. If setViewMatrix has not been
			 * called then this return value is undefined.
			 * @return The current view matrix. Undefined if not explicitly set.
			 */
			Matrix4x4 getViewMatrix() const { return m_viewMatrix; }

			/*
			 * @brief Count up the total number of vertices the renderer
			 * currently has to render.
			 * @return The number of vertices the renderer has to render at this
			 * point in time.
			 */
			std::size_t countTotalNumVertices();
		};
	} // namespace gfx
} // namespace qz
