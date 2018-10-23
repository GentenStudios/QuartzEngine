#pragma once

#ifdef __linux__
    #define PHX_LINUX
#elif defined(_WIN32)
    #define PHX_WINDOWS
#endif

// for testing purpose only
#define PHX_GL_DEBUG