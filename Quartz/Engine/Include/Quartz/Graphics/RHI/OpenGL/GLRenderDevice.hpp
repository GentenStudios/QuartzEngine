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

#include <Quartz/Graphics/RHI/IRenderDevice.hpp>
#include <Quartz/Graphics/RHI/InputLayout.hpp>
#include <Quartz/Graphics/RHI/OpenGL/GLShaderPipeline.hpp>
#include <Quartz/Graphics/RHI/OpenGL/GLTexture.hpp>
#include <Quartz/Graphics/RHI/OpenGL/GLVertexBuffer.hpp>
#include <Quartz/Math/Math.hpp>
#include <Quartz/Utilities/HandleAllocator.hpp>

#include <cstring>

namespace qz
{
	namespace gfx
	{
		namespace rhi
		{
			namespace gl
			{
				struct VertexStream
				{
					VertexBufferHandle buffer;
					int                stride = 0;
					int                offset = 0;
					bool               active = false;
				};

				struct Uniform
				{
					UniformType          type;
					GLint                location;
					ShaderPipelineHandle shader;
					const char*          name;

					union Userdata {
						float     vec2[2];
						float     vec3[3];
						float     vec4[4];
						Matrix4x4 mat4;

						Userdata ()
						{
							std::memset (mat4.elements, 0, 16 * sizeof (float));
						}

						~Userdata () {}
					} userdata;

					Uniform ();
				};

				class GLRenderDevice : public IRenderDevice
				{
				  public:
					GLRenderDevice ()                            = default;
					GLRenderDevice (const GLRenderDevice& other) = delete;

					bool isHandleValid (VertexBufferHandle handle) override;
					bool isHandleValid (ShaderPipelineHandle handle) override;
					bool isHandleValid (UniformHandle handle) override;
					bool isHandleValid (TextureHandle handle) override;

					void               create () override;
					VertexBufferHandle createVertexBuffer () override;
					void draw (std::size_t first, std::size_t count) override;
					void setVertexBufferStream (VertexBufferHandle buffer,
					                            int streamId, int stride,
					                            int offset) override;

					void setBufferData (VertexBufferHandle buffer, float* data,
					                    std::size_t sizebytes) override;
					void setShaderPipeline (
					    ShaderPipelineHandle shader) override;

					virtual ShaderPipelineHandle createShaderPipelineFromSource (
					    const std::string& dirpath,
					    const std::string& sourcecode,
					    const InputLayout& inputLayout);

					virtual ShaderPipelineHandle createShaderPipelineFromFile (
					    const std::string& filepath,
					    const InputLayout& inputLayout);

					UniformHandle createUniform (
					    ShaderPipelineHandle shaderHandle, const char* name,
					    UniformType type) override;
					
					void setUniformValue (UniformHandle uniform,
					                      const void* value, int num) override;

					TextureHandle createTexture (unsigned char* pixelData,
					                             std::size_t    width,
					                             std::size_t height) override;
					void setTexture (TextureHandle texture, int slot) override;

					void showShaderDebugUI () override;

					void freeVertexBuffer (VertexBufferHandle buffer) override;
					
					void freeShaderPipeline (
					    ShaderPipelineHandle shader) override;
					
					void freeUniform (UniformHandle uniform) override;
					void freeTexture (TextureHandle texture) override;

				  private:
					GLuint m_vao;

					utils::HandleAllocator<32, VertexBufferHandle>
					               m_vertexBufferHandles;
					GLVertexBuffer m_vertexBuffers[32];

					utils::HandleAllocator<32, ShaderPipelineHandle>
					                 m_shaderHandles;
					GLShaderPipeline m_shaders[32];

					utils::HandleAllocator<32, UniformHandle>
					        m_uniformHandleAllocator;
					Uniform m_uniforms[32];

					utils::HandleAllocator<32, TextureHandle>
					          m_textureHandleAllocator;
					GLTexture m_textures[32];

					ShaderPipelineHandle m_boundShader;
					TextureHandle        m_boundTexture;

					static constexpr int NUM_STREAMS = 32;
					VertexStream         m_vertexStreams[NUM_STREAMS];
				};
			} // namespace gl
		}     // namespace rhi
	}         // namespace gfx
} // namespace qz
