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
#include <Quartz/Core/Graphics/API/GraphicsResource.hpp>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			enum class BufferUsage : int
			{
				STATIC,
				DYNAMIC
			};

			enum class BufferTarget : int
			{
				ARRAY_BUFFER,
				INDEX_BUFFER,
				TEXTURE_BUFFER,
				UNIFORM_BUFFER
			};

			class IBuffer
			{
			public:
				static GraphicsResource<IBuffer> generateBuffer(BufferTarget target = BufferTarget::ARRAY_BUFFER, BufferUsage usage = BufferUsage::STATIC);

				virtual ~IBuffer() = default;

				virtual void bind() = 0;
				virtual void unbind() = 0;

				virtual void resize(unsigned int size) = 0;
				virtual void setData(unsigned int size, const void* data) = 0;

				template<typename T>
				T* retrieveDataPointer()
				{
					return static_cast<T*>(retrievePointerInternal());
				}

				virtual void releaseDataPointer() = 0;

			protected:
				virtual void* retrievePointerInternal() = 0;
			};
		}
	}
}

