add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Utilities)

add_subdirectory(Graphics)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(engineSources
	${voxelSources}
	${mathSources}
	${utilitySources}

	${graphicsSources}

	${currentDir}/Engine.cpp
	${currentDir}/QuartzPCH.cpp

	PARENT_SCOPE
)
