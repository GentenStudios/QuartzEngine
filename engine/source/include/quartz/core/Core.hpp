#pragma once

#define QZ_BUILD_DLL

#pragma warning(disable : 4251)

#if defined(_DEBUG)
#	define QZ_DEBUG
#endif

#if defined(_WIN32) || defined(_WIN64)
#   define QZ_PLATFORM_WINDOWS
#endif

#if defined(__linux__)
#   define QZ_PLATFORM_LINUX
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#	ifdef QZ_BUILD_DLL
#		ifdef __GNUC__
#			define QZ_API __attribute__((dllexport))
#		else
#			define QZ_API __declspec(dllexport)
#		endif
#	else
#		ifdef __GNUC__
#			define QZ_API __attribute__((dllimport))
#		else
#			define QZ_API __declspec(dllimport)
#		endif
#	endif
#else
#	if __GNUC__ >= 4
#		define QZ_API __attribute__((visibility ("default")))
#	else
#		define QZ_API
#	endif
#endif
