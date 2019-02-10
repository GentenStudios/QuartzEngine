#pragma once

#include <quartz/core/Core.hpp>

namespace qz
{
	namespace utils
	{
		class FileIO
		{
		public:
			static std::string readAllFile(const std::string& filepath);
		};
	}
}