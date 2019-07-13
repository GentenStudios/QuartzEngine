add_subdirectory(Events)
add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Graphics)
add_subdirectory(Utilities)
add_subdirectory(Platform)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(engineHeaders
	${voxelHeaders}

	${graphicsHeaders}
	${mathHeaders}
	${utilityHeaders}
	${platformHeaders}
	${eventHeaders}

	${currentDir}/Core.hpp
	${currentDir}/QuartzPCH.hpp
	${currentDir}/UniversalDoxygenComments.hpp

	PARENT_SCOPE
)
