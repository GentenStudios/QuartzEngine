set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(glAPIHeaders
	${currentDir}/GLCommon.hpp
	${currentDir}/GLVertexBuffer.hpp
	${currentDir}/GLShaderPipeline.hpp
	${currentDir}/GLTexture.hpp
	${currentDir}/GLRenderDevice.hpp
	
	PARENT_SCOPE
)
