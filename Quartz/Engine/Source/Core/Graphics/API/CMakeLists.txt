add_subdirectory(GL)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(apiSources
	${currentDir}/Context.cpp
	#	${currentDir}/IStateManager.cpp
	#${currentDir}/IBuffer.cpp
	${currentDir}/InputLayout.cpp
	#${currentDir}/ITexture.cpp
	#${currentDir}/ITextureArray.cpp
	#${currentDir}/IFramebuffer.cpp
	#${currentDir}/IShaderPipeline.cpp

	${glAPISources}

	PARENT_SCOPE
)
