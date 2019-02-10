set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(glAPISources
	${currentDir}/GLStateManager.cpp
	${currentDir}/GLBuffer.cpp
	${currentDir}/GLShaderPipeline.cpp
	${currentDir}/GLTexture.cpp
	${currentDir}/GLTextureArray.cpp
	${currentDir}/GLFramebuffer.cpp
    
	PARENT_SCOPE
)