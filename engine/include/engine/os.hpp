/**
 * @file os.hpp
 * @brief Detects operation system and sets definitions.
 *
 */

#pragma once

 /*
  *  __linux__       Defined on Linux
  *  __sun           Defined on Solaris
  *  __FreeBSD__     Defined on FreeBSD
  *  __NetBSD__      Defined on NetBSD
  *  __OpenBSD__     Defined on OpenBSD
  *  __APPLE__       Defined on Mac OS X
  *  __hpux          Defined on HP-UX
  *  __osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
  *  __sgi           Defined on Irix
  *  _AIX            Defined on AIX
  * _WIN32 OR _WIN64 Defined on Windows
 */

#if defined(_WIN32) || defined(_WIN64)
#   define PHX_OS_WINDOWS
#endif

#if defined(__linux__)
#   define PHX_OS_LINUX
#endif

// FOR TESTING PURPOSES ONLY
#define PHX_GL_DEBUG
