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

#include <Quartz/Core/Utilities/HandleAllocator.hpp>
#include <Quartz/Core/Graphics/API/InputLayout.hpp>

#define DEFINE_HANDLE(Name) \
		struct Name : public utils::Handle { }

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			DEFINE_HANDLE(VertexBufferHandle);
			DEFINE_HANDLE(ShaderPipelineHandle);
			DEFINE_HANDLE(UniformHandle);
			DEFINE_HANDLE(TextureHandle);

			enum class UniformType
			{
				SAMPLER, MAT4, VEC3, VEC2, COLOR3, INVALID
			};

			class IRenderDevice
			{
			public:
				virtual void create() = 0;
				virtual void draw(std::size_t first, std::size_t count) = 0;

				virtual VertexBufferHandle createVertexBuffer() = 0;
				virtual void setVertexBufferStream(VertexBufferHandle buffer, int streamId, int stride, int offset) = 0;
				virtual void setBufferData(VertexBufferHandle buffer, float *data, std::size_t sizebytes) = 0;
				
				virtual ShaderPipelineHandle createShaderPipeline(const std::string& filepath, const InputLayout& inputLayout) = 0;
				virtual void setShaderPipeline(ShaderPipelineHandle shader) = 0;

				virtual UniformHandle createUniform(ShaderPipelineHandle shader, const char* name, UniformType type) = 0;
				virtual void setUniformValue(UniformHandle uniform, const void* value, int num) = 0;

				virtual TextureHandle createTexture(unsigned char* pixelData, int width, int height) = 0;
				virtual void setTexture(TextureHandle texture, int slot) = 0;

				virtual void showShaderDebugUI() = 0;
			};
		}
	}
}

#undef DEFINE_HANDLE
