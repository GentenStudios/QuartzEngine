add_subdirectory(Graphics)
add_subdirectory(Math)
add_subdirectory(Platform)
add_subdirectory(Utilities)

set(coreSources
	${graphicsSources}
	${mathSources}
	${platformSources}
	${utilitySources}

	${CMAKE_CURRENT_LIST_DIR}/QuartzPCH.cpp

	PARENT_SCOPE
)
