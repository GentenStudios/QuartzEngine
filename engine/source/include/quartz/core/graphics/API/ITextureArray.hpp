#pragma once

#include <quartz/core/Core.hpp>

#include <quartz/core/graphics/API/GraphicsResource.hpp>
#include <quartz/core/graphics/API/ITexture.hpp>

#include <unordered_map>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			using TexCache = std::unordered_map<std::string, int>;

			class QZ_API ITextureArray : public ITextureObject
			{
			public:
				static GraphicsResource<ITextureArray> generateTextureArray();
				virtual ~ITextureArray() = default;

				virtual void setOptions(TextureOptions options) = 0;

				virtual void add(const std::string& path) = 0;

				virtual void reserve(const std::string& path) = 0;
				virtual void resolveReservations() = 0;

				virtual const TexCache& getTextureList() const = 0;
				virtual int getTexLayer(const std::string& path) = 0;

			protected:
				ITextureArray() = default;

				TexCache m_texNames;
				TexCache m_texReservations;

				int m_layerNumber = 0;
			};
		}
	}
}
