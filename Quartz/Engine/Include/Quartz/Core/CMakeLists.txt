add_subdirectory(Events)
add_subdirectory(Platform)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(coreHeaders
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
