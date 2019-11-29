add_subdirectory(Internal)
add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Utilities)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(engineHeaders
	${internalHeaders}

	${voxelHeaders}

	${mathHeaders}
	${utilityHeaders}
	${eventHeaders}

	${currentDir}/Core.hpp
	${currentDir}/QuartzPCH.hpp
	${currentDir}/UniversalDoxygenComments.hpp

	PARENT_SCOPE
)
