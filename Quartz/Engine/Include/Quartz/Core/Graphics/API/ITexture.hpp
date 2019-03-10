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

#include <string>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			enum class TexFilter : int
			{
				LINEAR,
				NEAREST
			};

			enum class TexFormat : int
			{
				RGB,
				RGBA,
				BGR,
				BGRA
			};

			enum class TexWrap : int
			{
				NONE,
				REPEAT,
				MIRRORED_REPEAT,
				CLAMP_TO_EDGE,
				CLAMP_TO_BORDER
			};

			struct TextureOptions
			{
				bool flipOnX;
				bool flipOnY;

				TexFormat format;
				TexFilter filter;
				TexWrap wrap;

				TextureOptions() :
					flipOnX(false),
					flipOnY(false),
					format(TexFormat::RGBA),
					filter(TexFilter::LINEAR),
					wrap(TexWrap::CLAMP_TO_EDGE)
				{}
			};

			class QZ_API ITextureObject
			{
			public:
				virtual ~ITextureObject() = default;

				virtual void bind(int slot = -1) const = 0;
				virtual void unbind() const = 0;
			};

			class QZ_API ITexture : public ITextureObject
			{
			public:
				static GraphicsResource<ITexture> generateTexture(TextureOptions options);

				virtual ~ITexture() = default;

				virtual void setOptions(TextureOptions options) = 0;

				virtual void setDataFromFile(const std::string& filepath) = 0;
				virtual void setDataFromMemory(const void* dataPointer) = 0;
			};
		}
	}
}

