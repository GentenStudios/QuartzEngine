/**
 * @file Core.hpp
 * @brief Core includes for the Project. Yay!
 *
 */

#pragma once

#if defined(_WIN32) || defined(_WIN64)
#   define PHX_OS_WINDOWS
#endif

#if defined(__linux__)
#   define PHX_OS_LINUX
#endif

#define PHX_DEBUG

// #ifdef DEBUG
// #	define PHX_DEBUG
// #endif

/// INCLUDE STREAMS ///
#include <iostream>
#include <fstream>
#include <sstream>

/// INCLUDE MATH ///
#include <cmath>

/// INCLUDE STL CONTAINERS ///
#include <string>
#include <vector>
#include <unordered_map>

/// INCLUDE CUSTOM THINGS. ///
#include <engine/core/utils/Logging.hpp>
