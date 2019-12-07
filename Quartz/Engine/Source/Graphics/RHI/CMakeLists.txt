add_subdirectory(OpenGL)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(rhiSources
	${glSources}

	${currentDir}/Context.cpp

	PARENT_SCOPE
)
