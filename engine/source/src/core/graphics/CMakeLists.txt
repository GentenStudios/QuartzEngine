add_subdirectory(API)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(graphicsSources
	${apiSources}

	${currentDir}/IWindow.cpp
	${currentDir}/SDLGUILayer.cpp

	PARENT_SCOPE
)
