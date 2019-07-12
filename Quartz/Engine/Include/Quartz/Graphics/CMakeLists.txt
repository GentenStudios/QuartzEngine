add_subdirectory(RHI)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(graphicsHeaders
	${apiHeaders}
	
	${currentDir}/Camera.hpp
	${currentDir}/Mesh.hpp
	${currentDir}/ForwardMeshRenderer.hpp
	${currentDir}/ImGuiExtensions.hpp

	PARENT_SCOPE
)
