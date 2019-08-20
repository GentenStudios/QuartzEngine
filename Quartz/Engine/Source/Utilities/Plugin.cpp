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

#include <Quartz/QuartzPCH.hpp>
#include <Quartz/Utilities/Plugin.hpp>

using namespace qz::utils;

Plugin::Plugin() :
    m_hInstance(NULL)
    , m_path("")
    , m_loaded(false)
{}

Plugin::Plugin(const std::string& path) :
    m_hInstance(NULL)
    , m_path(path)
    , m_loaded(false)
{
    load(m_path);
}

Plugin::~Plugin()
{
    unload();
}

void Plugin::load(const std::string& path)
{
    if (m_loaded)
        unload();
    m_path = path;
    
#if defined(QZ_PLATFORM_WINDOWS)
    if (NULL == (m_hInstance = LoadLibrary(m_path.c_str())))
    {
        throw std::system_error(
            std::error_code(::GetLastError(), std::system_category())
            , "Couldn't load the library"
        );
    }
#elif defined(QZ_PLATFORM_LINUX)
    if (NULL == (m_hInstance = dlopen(m_path.c_str(), RTLD_NOW | RTLD_GLOBAL)))
    {
        throw std::system_error(
            std::error_code(errno, std::system_category())
            , "Couldn't load the library, " + std::string(dlerror())
        );
    }
#endif
    m_loaded = true;
}

void Plugin::unload()
{
    if (m_loaded)
    {
#if defined(QZ_PLATFORM_WINDOWS)
        FreeLibrary(m_hInstance);
#elif defined(QZ_PLATFORM_LINUX)
        dlclose(m_hInstance);
#endif
    }
}
