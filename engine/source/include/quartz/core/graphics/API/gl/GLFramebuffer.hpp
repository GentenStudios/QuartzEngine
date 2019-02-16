#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/graphics/API/gl/GLCommon.hpp>
#include <quartz/core/graphics/API/IFramebuffer.hpp>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				class QZ_API GLFramebuffer : public IFramebuffer
				{
				public:
					GLFramebuffer();
					~GLFramebuffer();

					GLFramebuffer(const GLFramebuffer& o) = default;
					GLFramebuffer& operator=(const GLFramebuffer& o) = default;

					GLFramebuffer(GLFramebuffer&& o) noexcept;
					GLFramebuffer& operator=(GLFramebuffer&& o) noexcept;

					void bind() const override;
					void unbind() const override;

					void reset() override;

					void getSize(int& x, int& y) const override;

					ITexture* getTexture() const override;

				private:
					unsigned int m_id;
				};
			}
		}
	}
}
