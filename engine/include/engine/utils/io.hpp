#pragma once

#include "engine/common.hpp"

namespace phx
{

	class File
	{
	public:
		static std::string readFile(const std::string& filePath);
	};

}