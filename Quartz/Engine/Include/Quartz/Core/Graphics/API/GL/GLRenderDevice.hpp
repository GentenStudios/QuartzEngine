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

#include <Quartz/Core/Graphics/API/IRenderDevice.hpp>
#include <Quartz/Core/Utilities/HandleAllocator.hpp>
#include <Quartz/Core/Graphics/API/InputLayout.hpp>
#include <Quartz/Core/Graphics/API/GL/GLVertexBuffer.hpp>
#include <Quartz/Core/Graphics/API/GL/GLShaderPipeline.hpp>
#include <Quartz/Core/Graphics/API/GL/GLTexture.hpp>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				struct VertexStream
				{
					VertexBufferHandle buffer;
					int stride = 0;
					int offset = 0;
					bool active = false;
				};

				struct Uniform
				{
					UniformType type;
					GLint location;
					ShaderPipelineHandle shader;
					const char* name;

					union
					{
						float vec2[2];
						float vec3[3];
						float vec4[4];
					} userdata;

					Uniform();
				};

				class GLRenderDevice : public IRenderDevice
				{
				public:
					GLRenderDevice() = default;
					~GLRenderDevice() = default;

					GLRenderDevice(const GLRenderDevice& other) = delete;

					void create() override;
					VertexBufferHandle createVertexBuffer() override;
					void draw(std::size_t first, std::size_t count) override;
					void setVertexBufferStream(VertexBufferHandle buffer, int streamId, int stride, int offset) override;

					void setBufferData(VertexBufferHandle buffer, float *data, std::size_t sizebytes) override;
					ShaderPipelineHandle createShaderPipeline(const std::string& shadersource, const InputLayout& inputLayout) override;
					void setShaderPipeline(ShaderPipelineHandle shader) override;

					UniformHandle createUniform(ShaderPipelineHandle shaderHandle, const char* name, UniformType type) override;
					void setUniformValue(UniformHandle uniform, const void* value, int num) override;

					TextureHandle createTexture(unsigned char* pixelData, int width, int height) override;
					void setTexture(TextureHandle texture, int slot) override;

					void showShaderDebugUI() override;

				private:
					GLuint m_vao;

					utils::HandleAllocator<32, VertexBufferHandle>   m_vertexBufferHandles;
					GLVertexBuffer                                   m_vertexBuffers[32];

					utils::HandleAllocator<32, ShaderPipelineHandle> m_shaderHandles;
					GLShaderPipeline                                 m_shaders[32];

					utils::HandleAllocator<32, UniformHandle>        m_uniformHandleAllocator;
					Uniform                                          m_uniforms[32];

					utils::HandleAllocator<32, TextureHandle>        m_textureHandleAllocator;
					GLTexture                                        m_textures[32];

					ShaderPipelineHandle                             m_boundShader;

					static constexpr int                             NUM_STREAMS = 32;
					VertexStream                                     m_vertexStreams[NUM_STREAMS];
				};
			}
		}
	}
}
