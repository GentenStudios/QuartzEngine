#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/graphics/API/ITextureArray.hpp>

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
