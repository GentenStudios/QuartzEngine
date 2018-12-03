set(mathSourceDir ${CMAKE_CURRENT_LIST_DIR})

set(mathSources
    ${mathSourceDir}/Vector2.cpp
    ${mathSourceDir}/Vector3.cpp
    ${mathSourceDir}/Matrix4x4.cpp
)

source_group("Source Files\\Core\\Math" FILES ${mathSources})

set(engineSources
    ${engineSources}
    ${mathSources}
    CACHE INTERNAL "Global Engine Sources"
)