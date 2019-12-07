add_subdirectory(Internal)
add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Utilities)

add_subdirectory(Graphics)
add_subdirectory(Events)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(engineHeaders
	${internalHeaders}
	${voxelHeaders}
	${mathHeaders}
	${utilityHeaders}
	
	${graphicsHeaders}
	${eventHeaders}

	${currentDir}/Core.hpp
	${currentDir}/Engine.hpp
	${currentDir}/NonCopyable.hpp
	${currentDir}/QuartzPCH.hpp
	${currentDir}/UniversalDoxygenComments.hpp

	PARENT_SCOPE
)
