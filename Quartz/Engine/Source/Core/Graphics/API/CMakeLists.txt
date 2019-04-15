add_subdirectory(GL)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(apiSources
	${currentDir}/InputLayout.cpp

	${glAPISources}

	PARENT_SCOPE
)
