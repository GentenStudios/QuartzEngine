#pragma once

#if defined(_DEBUG)
#	define QZ_DEBUG
#endif

// Determine the compiler and set the corresponding defines for it.
#ifdef _MSC_VER
#	define QZ_MSVC
#elif defined(__clang__)
#	define QZ_CLANG
#elif defined(__GNUC__)
#	define QZ_GNUC
#endif

// Determine the OS and set the corresponding defines for it.
#if defined(_WIN32) || defined(_WIN64)
#   define QZ_PLATFORM_WINDOWS
#elif defined(__linux__)
#   define QZ_PLATFORM_LINUX
#endif

#if defined(QZ_PLATFORM_WINDOWS)
#	define IF_WINDOWS(x) x
#else
#	define IF_WINDOWS(x)
#endif

#if defined(QZ_PLATFORM_LINUX)
#	define IF_LINUX(x) x
#else
#	define IF_LINUX(x)
#endif

///////////////////// TEMPORARY
///
#ifndef QZ_PLATFORM_WINDOWS
#	error Only MSFT Windows is supported as of right now.
#endif
///
///////////////////// END TEMPORARY
