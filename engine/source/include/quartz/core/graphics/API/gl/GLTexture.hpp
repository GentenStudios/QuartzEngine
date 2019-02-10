#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/graphics/API/gl/GLCommon.hpp>
#include <quartz/core/graphics/API/ITexture.hpp>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				class QZ_API GLTexture : public ITexture
				{
				public:
					GLTexture();
					~GLTexture();

					GLTexture(const GLTexture& o) = default;
					GLTexture& operator=(const GLTexture& o) = default;

					GLTexture(GLTexture&& o) noexcept;
					GLTexture& operator=(GLTexture&& o) noexcept;

					void setOptions(TextureOptions options) override;

					void bind(int slot = -1) const override;
					void unbind() const override;

					void setDataFromFile(const std::string& filepath) override;
					void setDataFromMemory(const void* dataPointer) override;

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
