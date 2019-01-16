set(utilsIncludeDir ${CMAKE_CURRENT_LIST_DIR})

set(utilHeaders
    ${utilsIncludeDir}/IO.hpp
    ${utilsIncludeDir}/Logging.hpp
    ${utilsIncludeDir}/Config.hpp
    ${utilsIncludeDir}/ThreadPool.hpp
)

source_group("Header Files\\Core\\Utils" FILES ${utilHeaders})

set(engineHeaders
    ${engineHeaders}
    ${utilHeaders}
    CACHE INTERNAL "Global Engine Headers"
)