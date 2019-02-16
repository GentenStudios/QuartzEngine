#pragma once

#include <quartz/core/Core.hpp>

#include <quartz/core/graphics/API/GraphicsResource.hpp>

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
