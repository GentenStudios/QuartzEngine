add_subdirectory(API)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(graphicsHeaders
	${apiHeaders}
	
	${currentDir}/IWindow.hpp
	${currentDir}/Renderable3D.hpp
	${currentDir}/Model.hpp
	${currentDir}/Renderer3D.hpp
	
	PARENT_SCOPE
)
