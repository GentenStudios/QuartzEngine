add_subdirectory(Graphics)
add_subdirectory(Math)
add_subdirectory(Utilities)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(coreSources
	${graphicsSources}
	${mathSources}
	${platformSources}
	${utilitySources}

	${currentDir}/Engine.cpp

	${currentDir}/QuartzPCH.cpp

	PARENT_SCOPE
)
