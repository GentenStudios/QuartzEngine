set(platformSourceDir ${CMAKE_CURRENT_LIST_DIR})

set(platformSources
    ${platformSourceDir}/SDL/SDLWindow.cpp
)

source_group("Source Files\\Core\\Platform" FILES ${platformSources})

set(engineSources
    ${engineSources}
    ${platformSources}
    CACHE INTERNAL "Global Engine Sources"
)
