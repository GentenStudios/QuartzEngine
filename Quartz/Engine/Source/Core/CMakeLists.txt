add_subdirectory(Platform)

set(coreSources
        ${platformSources}

	${CMAKE_CURRENT_LIST_DIR}/QuartzPCH.cpp

	PARENT_SCOPE
)
