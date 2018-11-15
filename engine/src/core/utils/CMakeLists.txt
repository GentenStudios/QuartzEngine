set(utilsSourceDir ${CMAKE_CURRENT_LIST_DIR})

set(utilsSources
    ${utilsSourceDir}/IO.hpp
    ${utilsSourceDir}/Logging.hpp
)

source_group("Source Files\\Core\\Utils" FILES ${utilSources})

set(engineSources
    ${engineSources}
    ${utilSources}
    CACHE INTERNAL "Global Engine Sources"
)