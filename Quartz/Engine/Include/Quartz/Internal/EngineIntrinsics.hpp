#pragma once

#include <Quartz/Internal/EngineDefines.hpp>

#include <cassert>

#if defined(QZ_MSVC)
#	define QZ_FORCE_INLINE __forceinline
#	define QZ_NORETURN __declspec(noreturn)
#elif defined(QZ_CLANG) || defined(QZ_GNUC)
#	define QZ_FORCE_INLINE __attribute__((always_inline))
#	define QZ_NORETURN __attribute__((noreturn))
#endif

#if defined(QZ_DEBUG)
#	if defined(QZ_MSVC)
#		define BREAKPOINT() __debugbreak()
#	elif defined(QZ_CLANG) || defined(PC_GNUC)
#		define BREAKPOINT() __builtin_trap()
#	endif
#else
#	define BREAKPOINT()
#endif

// TODO: (vfadia) Log the assertion fail & allow all the extra arguments to go straight to the logQZr and all that jazz.
#if defined(QZ_DEBUG)
#	define QZ_ASSERT(condition, ...) { assert (condition); }
#else
#	define QZ_ASSERT(condition, ...) 
#endif
