/**
 * @file IO.hpp
 * @brief Class(es) for File INPUT and OUTPUT. Will be expanded to more when someone can be bothered to do boring shit.
 * 
 */

#pragma once

#include <engine/core/Core.hpp>

namespace phx
{
	/**
	 * @brief Class for File management, quite sparse now, but will be populated at a later date.
	 * 
	 */
	class File
	{
	public:
		static std::string readFile(const std::string& filePath);
	};

}