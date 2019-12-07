add_subdirectory(OpenGL)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(rhiHeaders
	${glHeaders}

	PARENT_SCOPE
)
