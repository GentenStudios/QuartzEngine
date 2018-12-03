set(platformIncludeDir ${CMAKE_CURRENT_LIST_DIR})

set(platformHeaders
    ${platformIncludeDir}/SDL/SDLWindow.hpp
)

source_group("Header Files\\Core\\Platform" FILES ${platformHeaders})

set(engineHeaders
    ${engineHeaders}
    ${platformHeaders}
    CACHE INTERNAL "Global Engine Headers"
)