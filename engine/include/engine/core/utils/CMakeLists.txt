set(utilsIncludeDir ${CMAKE_CURRENT_LIST_DIR})

set(utilHeaders
    ${utilsIncludeDir}/IO.hpp
    ${utilsIncludeDir}/Logging.hpp
)

source_group("Header Files\\Core\\Utils" FILES ${utilHeaders})

set(engineHeaders
    ${engineHeaders}
    ${utilHeaders}
    CACHE INTERNAL "Global Engine Headers"
)