#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/graphics/API/GraphicsResource.hpp>
#include <quartz/core/graphics/API/ITexture.hpp>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			class QZ_API IFramebuffer
			{
			public:
				static GraphicsResource<IFramebuffer> generateFramebuffer();
				virtual ~IFramebuffer() = default;

				virtual void bind() const = 0;
				virtual void unbind() const = 0;

				virtual void reset() = 0;

				virtual void getSize(int& x, int& y) const = 0;

				virtual ITexture* getTexture() const = 0;
			};
		}
	}
}
