add_subdirectory(Platform)
add_subdirectory(Utilities)

set(coreSources
        ${platformSources}
	${utilitySources}

	${CMAKE_CURRENT_LIST_DIR}/QuartzPCH.cpp

	PARENT_SCOPE
)
