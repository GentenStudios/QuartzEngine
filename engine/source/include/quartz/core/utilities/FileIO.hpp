#pragma once

#include <quartz/core/Core.hpp>

namespace qz
{
	namespace utils
	{
		/**
		 * @brief File Input/Output wrapping class.
		 */
		class QZ_API FileIO
		{
		public:
			/**
			 * @brief Reads a whole file into a string.
			 * @param filepath The path to the file needing to be read.
			 * @return A string containing the contents of the file.
			 */
			static std::string readAllFile(const std::string& filepath);
		};
	}
}