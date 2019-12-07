add_subdirectory(RHI)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(graphicsSources
	${rhiSources}

	${currentDir}/IWindow.cpp

	PARENT_SCOPE
)
