add_subdirectory(OpenGL)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(apiSources
	${currentDir}/Context.cpp
	${currentDir}/InputLayout.cpp

	${glAPISources}

	PARENT_SCOPE
)
