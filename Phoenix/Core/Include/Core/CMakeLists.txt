add_subdirectory(Voxels)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(coreHeaders
	${voxelHeaders}
	
	${currentDir}/LuaAPI.hpp

	PARENT_SCOPE
)
