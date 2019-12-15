// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// Internal Includes
#include <Quartz/Utilities/AssetManagement.hpp>

// External Includes
//...

// Standard Includes
#include <cstdio>
#include <cstdlib>
//#include <iostream>
#include <filesystem>

// Complex Includes
#ifdef OS_WINDOWS
#	include <windows.h> //GetModuleFileNameW
#else
#	include <limits.h>
#	include <unistd.h> //readlink
#endif

using namespace qz::utils;

// Horizontal namespace shrinking to improve code readability.
#define FS std::filesystem

FS::path get_exec_path()
{
#ifdef OS_WINDOWS
	wchar_t path[MAX_PATH] = {0};
	GetModuleFileNameW(NULL, path, MAX_PATH);
	return path;
#else
	char    result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	return std::string(result, (count > 0) ? count : 0);
#endif
};

FS::path getOSDataStore()
{
	return FS::weakly_canonical(
#if defined(OS_WINDOWS)
	    ( // Nest within make_preffered to make this a true windows path.
	        FS::path(std::getenv("APPDATA")) / "Local/Share"

	        )
	        .make_preffered();
#elif defined(OS_MAC) || defined(OS_DARWIND)
	    FS::path(std::string(std::getenv("HOME"))) / "Library/Preferences"
#else
	    // defined(OS_LINUX) || defined(OS_ANDROID) || defined(OS_SUNOS)
	    // pretty much all other platforms. Although we can append as necessary.
	    FS::path(std::string(std::getenv("HOME"))) / ".local/share"
#endif
	);
};

inline void getAssetStore()
{
	FS::path executablePath = FS::get_exec_path();

#if defined(DEVELOPMENT_BUILD) || defined(PORTABLE_BUILD)
	// the executable path should already be weakly_canonical
	// no reason to wrap.
	executablePath.parent_path() / (executablePath.filename() + "_Assets")

#else
	assetStore = getOSDataStore() / executablePath.filename()
#endif
};

inline void getAssetStore(const std::string programName)
{
	FS::path executablePath = FS::get_exec_path();

#if defined(DEVELOPMENT_BUILD) || defined(PORTABLE_BUILD)
	// the executable path should already be weakly_canonical
	// no reason to wrap.
	executablePath.parent_path() / (programName + "_Assets")

#else
	assetStore = getOSDataStore() / programName
#endif
};

// Clean up MACRO namespace polution
#undef FS
