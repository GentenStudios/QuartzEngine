set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(glAPISources
	${currentDir}/GLVertexBuffer.cpp
	${currentDir}/GLShaderPipeline.cpp
	${currentDir}/GLTexture.cpp
	${currentDir}/GLRenderDevice.cpp
    
	${currentDir}/GLGUILayer.cpp
	${currentDir}/GLWindow.cpp

	PARENT_SCOPE
)
