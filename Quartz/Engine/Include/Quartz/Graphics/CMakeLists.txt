add_subdirectory(RHI)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(graphicsHeaders
	${rhiHeaders}

	${currentDir}/IWindow.hpp

	PARENT_SCOPE
)
