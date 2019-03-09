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

#include <Quartz/Core/Core.hpp>
#include <Quartz/Core/Graphics/API/IStateManager.hpp>
#include <Quartz/Core/Graphics/API/GL/GLBuffer.hpp>

#include <vector>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				class QZ_API GLStateManager : public IStateManager
				{
				public:
					GLStateManager();
					~GLStateManager();

					GLStateManager(const GLStateManager& o) = default;
					GLStateManager& operator=(const GLStateManager& o) = default;
					GLStateManager(GLStateManager&& o) noexcept;
					GLStateManager& operator=(GLStateManager&& o) noexcept;

					void bind() const override;
					void unbind() const override;

					GraphicsResource<IBuffer> retrieveBuffer(unsigned int index = 0) override;

					void attachBuffer(GraphicsResource<IBuffer> buffer) override;
					void attachBufferLayout(const BufferLayout& bufferLayout, GraphicsResource<IShaderPipeline> shader) override;

					void render(unsigned int start, unsigned int count) const override;

				private:
					unsigned int m_id;
					
					std::vector<GraphicsResource<IBuffer>> m_buffers;
				};
			}
		}
	}
}

