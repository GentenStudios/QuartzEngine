set(mathIncludeDir ${CMAKE_CURRENT_LIST_DIR})

set(mathHeaders
    ${mathIncludeDir}/Vector2.hpp
    ${mathIncludeDir}/Vector3.hpp
    ${mathIncludeDir}/Matrix4x4.hpp
    ${mathIncludeDir}/MathUtils.hpp
	${mathIncludeDir}/Ray.hpp
)

source_group("Header Files\\Core\\Math" FILES ${mathHeaders})

set(engineHeaders
    ${engineHeaders}
    ${mathHeaders}
    CACHE INTERNAL "Global Engine Headers"
)