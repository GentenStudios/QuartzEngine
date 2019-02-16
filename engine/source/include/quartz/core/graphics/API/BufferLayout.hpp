#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/graphics/API/GFXTypes.hpp>

#include <vector>
#include <string>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			struct BufferAttribute
			{
				std::string name;

				DataType type;

				int elementCount;
				int countTillNextElement;
				std::size_t offset;
				bool normalised;
			};

			class QZ_API BufferLayout
			{
			public:
				BufferLayout() = default;
				~BufferLayout() = default;

				BufferLayout(const BufferLayout& other) = default;
				BufferLayout& operator=(const BufferLayout& o) = default;
				BufferLayout(BufferLayout&& other) = default;
				BufferLayout& operator=(BufferLayout&& o) = default;

				void registerAttribute(const std::string& name, DataType type, int count, int stride, std::size_t offset, bool normalised);
				void registerAttribute(BufferAttribute attribute);

				const std::vector<BufferAttribute>& getLayouts() const;

			private:
				std::vector<BufferAttribute> m_bufferLayout;
			};
		}
	}
}
