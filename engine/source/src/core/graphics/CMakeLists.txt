add_subdirectory(API)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(graphicsSources
	${apiSources}

	${currentDir}/IWindow.cpp
	${currentDir}/Camera.cpp

	PARENT_SCOPE
)