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

#pragma once

#include <Quartz/Core.hpp>

#if defined(QZ_PLATFORM_WINDOWS)
    #include <Windows.h>
#elif defined(QZ_PLATFORM_LINUX)
    #include <dlfcn.h>
#endif

#include <string>
#include <system_error>
#include <exception>

namespace qz
{
    namespace utils
    {
        class Plugin
        {
        public:
            Plugin();
            Plugin(const std::string& path);
            ~Plugin();

            void load(const std::string& path);
            void unload();

            template <typename T>
            T get(const std::string& procname)
            {
                T funcptr;

#if defined(QZ_PLATFORM_WINDOWS)
                if (NULL == (funcptr = reinterpret_cast<T>(GetProcAddress(m_hInstance, procname.c_str()))))
                {
                    throw std::system_error(
                        std::error_code(::GetLastError(), std::system_category())
                        , std::string("Couldn't find ") + procname
                    );
                }
#elif defined(QZ_PLATFORM_LINUX)
                if (NULL == (funcptr = reinterpret_cast<T>(dlsym(m_hInstance, procname.c_str()))))
                {
                    throw std::system_error(
                        std::error_code(errno, std::system_category())
                        , std::string("Couldn't find ") + procname + ", " + std::string(dlerror())
                    );
                }
#endif
                return funcptr;
            }
        
        private:
#if defined(QZ_PLATFORM_WINDOWS)
            HINSTANCE m_hInstance;
#elif defined(QZ_PLATFORM_LINUX)
            void* m_hInstance;
#endif
            std::string m_path;
            bool m_loaded;
        };

    }  // namespace utils
}  // namespace qz