#pragma once

#include <engine/core/Core.hpp>

namespace phx
{

	class File
	{
	public:
		static std::string readFile(const std::string& filePath);
	};

}