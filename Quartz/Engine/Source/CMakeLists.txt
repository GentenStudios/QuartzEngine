add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Utilities)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(engineSources
	${voxelSources}
	${mathSources}
	${utilitySources}

	${currentDir}/QuartzPCH.cpp

	PARENT_SCOPE
)
