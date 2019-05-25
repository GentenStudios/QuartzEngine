add_subdirectory(API)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(graphicsHeaders
	${apiHeaders}
	
	${currentDir}/IWindow.hpp
	${currentDir}/Camera.hpp
	${currentDir}/Mesh.hpp
	${currentDir}/ForwardMeshRenderer.hpp

	PARENT_SCOPE
)
