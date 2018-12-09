set(eventIncludeDir ${CMAKE_CURRENT_LIST_DIR})

set(eventHeaders
    ${eventIncludeDir}/Keys.hpp
	${eventIncludeDir}/Mouse.hpp
)

source_group("Header Files\\Core\\Events" FILES ${eventHeaders})

set(engineHeaders
    ${engineHeaders}
    ${eventHeaders}
    CACHE INTERNAL "Global Engine Headers"
)