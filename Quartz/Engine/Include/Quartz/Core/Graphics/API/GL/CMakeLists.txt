set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(glAPIHeaders
	${currentDir}/GLCommon.hpp
	${currentDir}/GLBuffer.hpp
	${currentDir}/GLFramebuffer.hpp
	${currentDir}/GLShaderPipeline.hpp
	${currentDir}/GLTexture.hpp
	${currentDir}/GLTextureArray.hpp
	${currentDir}/GLStateManager.hpp
	
	PARENT_SCOPE
)
