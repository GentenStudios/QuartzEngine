set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(glAPISources
	${currentDir}/GLVertexBuffer.cpp
	${currentDir}/GLShaderPipeline.cpp
	${currentDir}/GLTexture.cpp
	${currentDir}/GLRenderDevice.cpp
    
	PARENT_SCOPE
)
