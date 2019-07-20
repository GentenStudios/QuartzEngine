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

#include <Quartz/Graphics/RHI/InputLayout.hpp>
#include <Quartz/Utilities/HandleAllocator.hpp>

#define DEFINE_HANDLE(Name)                                                    \
	struct Name : public utils::HandleBase                                     \
	{                                                                          \
	};                                                                         \
	inline bool operator== (const Name& left, const Name& right)               \
	{                                                                          \
		return left.get () == right.get ();                                    \
	}

namespace qz
{
	namespace gfx
	{
		namespace rhi
		{
			DEFINE_HANDLE (VertexBufferHandle);
			DEFINE_HANDLE (ShaderPipelineHandle);
			DEFINE_HANDLE (UniformHandle);
			DEFINE_HANDLE (TextureHandle);

			enum class UniformType
			{
				SAMPLER,
				MAT4,
				VEC3,
				VEC2,
				COLOR3,
				INVALID
			};

			class IRenderDevice
			{
			  public:
				virtual ~IRenderDevice () {}

				virtual bool isHandleValid (VertexBufferHandle handle)   = 0;
				virtual bool isHandleValid (ShaderPipelineHandle handle) = 0;
				virtual bool isHandleValid (UniformHandle handle)        = 0;
				virtual bool isHandleValid (TextureHandle handle)        = 0;

				/**
				 * @brief Initialise the RenderDevice. Must be called before
				 *        any other methods on the RenderDevice.
				 */
				virtual void create () = 0;

				/**
				 * @brief Draw a non-indexed set of vertices (as triangles).
				 * @param first The index of the first vertex to draw.
				 * @param count The number of vertices to draw.
				 */
				virtual void draw (std::size_t first, std::size_t count) = 0;

				/**
				 * @brief Create a vertex buffer.
				 * @return A handle pointing to a vertex buffer ready for use.
				 */
				virtual VertexBufferHandle createVertexBuffer ()          = 0;
				virtual void freeVertexBuffer (VertexBufferHandle buffer) = 0;

				virtual void setVertexBufferStream (VertexBufferHandle buffer,
				                                    int streamId, int stride,
				                                    int offset) = 0;

				virtual void setBufferData (VertexBufferHandle buffer,
				                            float*             data,
				                            std::size_t        sizebytes) = 0;

				/**
				 * @brief Create shader from source code.
				 * @param dirpath path to directory used as working directory
				 * when parsing the source code.
				 * (#include directives will be intepreted relative to this dir
				 * )
				 * @param sourcecode The shader source code. Should contain all
				 * necessary shader stages.
				 * @param inputlayout Specificy the layout of that data passed
				 * into the shader.
				 * @return Handle to the newly created shader
				 */
				virtual ShaderPipelineHandle createShaderPipelineFromSource (
				    const std::string& dirpath, const std::string& sourcecode,
				    const InputLayout& inputLayout) = 0;

				virtual ShaderPipelineHandle createShaderPipelineFromFile (
				    const std::string& filepath,
				    const InputLayout& inputLayout) = 0;

				virtual void
				setShaderPipeline (ShaderPipelineHandle shader) = 0;

				virtual void
				freeShaderPipeline (ShaderPipelineHandle shader) = 0;

				virtual UniformHandle
				createUniform (ShaderPipelineHandle shader, const char* name,
				               UniformType type) = 0;

				virtual void setUniformValue (UniformHandle uniform,
				                              const void* value, int num) = 0;

				virtual void freeUniform (UniformHandle uniform) = 0;

				virtual TextureHandle createTexture (unsigned char* pixelData,
				                                     std::size_t    width,
				                                     std::size_t    height) = 0;

				virtual void setTexture (TextureHandle texture, int slot) = 0;
				virtual void freeTexture (TextureHandle texture)          = 0;
				virtual void showShaderDebugUI ()                         = 0;
			};
		} // namespace rhi
	}     // namespace gfx
} // namespace qz

#undef DEFINE_HANDLE
