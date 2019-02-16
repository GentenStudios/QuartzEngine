add_subdirectory(math)
add_subdirectory(events)
add_subdirectory(graphics)
add_subdirectory(platform)
add_subdirectory(utilities)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(coreHeaders
	${mathHeaders}
	${eventHeaders}
	${graphicsHeaders}
	${platformHeaders}
	${utilityHeaders}

	${currentDir}/Core.hpp
	${currentDir}/Application.hpp
	${currentDir}/EntryPoint.hpp

	${currentDir}/UniversalDoxygenComments.hpp
	${currentDir}/QuartzPCH.hpp
	
	PARENT_SCOPE
)
