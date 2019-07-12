add_subdirectory(Events)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(coreHeaders
        ${eventHeaders}

	${currentDir}/Core.hpp
	${currentDir}/Application.hpp
	${currentDir}/EntryPoint.hpp

	${currentDir}/UniversalDoxygenComments.hpp
	${currentDir}/QuartzPCH.hpp
	
	PARENT_SCOPE
)
