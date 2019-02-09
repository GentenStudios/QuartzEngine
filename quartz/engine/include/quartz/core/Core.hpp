/**
 * @file Core.hpp
 * @brief Core includes for the Project. Yay!
 *
 */

#pragma once

#if defined(_WIN32) || defined(_WIN64)
#   define QZ_OS_WINDOWS
#endif

#if defined(__linux__)
#   define QZ_OS_LINUX
#endif

#define QZ_DEBUG

/// INCLUDE STREAMS ///
#include <iostream>
#include <fstream>
#include <sstream>

/// INCLUDE STL CONTAINERS ///
#include <string>
#include <vector>
#include <unordered_map>

/// INCLUDE CUSTOM THINGS. ///
#include <quartz/core/utils/Logging.hpp>
