set(utilsSourceDir ${CMAKE_CURRENT_LIST_DIR})

set(utilSources
    ${utilsSourceDir}/IO.cpp
    ${utilsSourceDir}/Logging.cpp
    ${utilsSourceDir}/Config.cpp
)

source_group("Source Files\\Core\\Utils" FILES ${utilSources})

set(engineSources
    ${engineSources}
    ${utilSources}
    CACHE INTERNAL "Global Engine Sources"
)
