add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Utilities)
add_subdirectory(Platform)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(engineSources
	${voxelSources}
	${mathSources}
	${utilitySources}
	${platformSources}

	${currentDir}/QuartzPCH.cpp

	PARENT_SCOPE
)
