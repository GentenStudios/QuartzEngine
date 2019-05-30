add_subdirectory(RHI)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(graphicsSources
	${apiSources}

	${currentDir}/IWindow.cpp
	${currentDir}/Camera.cpp
	${currentDir}/ForwardMeshRenderer.cpp
	${currentDir}/Mesh.cpp
	${currentDir}/ImGuiExtensions.cpp

	PARENT_SCOPE
)
