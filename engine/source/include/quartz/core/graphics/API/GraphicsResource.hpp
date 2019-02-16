#pragma once

#include <memory>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			template <typename T>
			using GraphicsResource = std::shared_ptr<T>;
		}
	}
}
