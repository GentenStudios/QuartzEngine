add_subdirectory(Math)
add_subdirectory(Events)
add_subdirectory(Graphics)
add_subdirectory(Platform)
add_subdirectory(Utilities)

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
