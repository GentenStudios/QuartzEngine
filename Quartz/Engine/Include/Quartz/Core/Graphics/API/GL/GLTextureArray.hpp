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
#include <Quartz/Core/Graphics/API/ITextureArray.hpp>

#include <glad/glad.h>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				class QZ_API GLTextureArray : public ITextureArray
				{
				public:
					GLTextureArray();
					~GLTextureArray();

					GLTextureArray(const GLTextureArray& o) = default;
					GLTextureArray& operator=(const GLTextureArray& o) = default;

					GLTextureArray(GLTextureArray&& o) noexcept;
					GLTextureArray& operator=(GLTextureArray&& o) noexcept;

					void setOptions(TextureOptions options) override;

					void add(const std::string& filepath) override;

					void reserve(const std::string& filepath) override;
					void resolveReservations() override;

					void bind(int slot = -1) const override;
					void unbind() const override;

					const TexCache& getTextureList() const override;
					int getTexLayer(const std::string& path) override;

				protected:
					TexCache m_texNames;
					TexCache m_texReservations;

					int m_layerNumber = 0;

				private:
					unsigned int m_id;
					mutable int m_slot;

					bool m_flipOnX;
					bool m_flipOnY;

					GLenum m_format;
					GLenum m_filter;
					GLenum m_wrap;
				};
			}
		}
	}
}

