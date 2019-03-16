set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(glAPIHeaders
	${currentDir}/GLCommon.hpp
	${currentDir}/GLVertexBuffer.hpp
	#${currentDir}/GLFramebuffer.hpp
	#	${currentDir}/GLShaderPipeline.hpp
	#${currentDir}/GLTexture.hpp
	#${currentDir}/GLTextureArray.hpp
	#${currentDir}/GLStateManager.hpp
	${currentDir}/GLRenderDevice.hpp
	
	PARENT_SCOPE
)
