add_subdirectory(Voxels)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(phoenixSources
	${voxelSources}

	${currentDir}/LuaAPI.cpp

	PARENT_SCOPE
)