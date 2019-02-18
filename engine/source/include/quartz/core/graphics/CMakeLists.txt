add_subdirectory(API)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(graphicsHeaders
	${apiHeaders}
	
	${currentDir}/IWindow.hpp
	${currentDir}/SDLGUILayer.hpp

	PARENT_SCOPE
)
