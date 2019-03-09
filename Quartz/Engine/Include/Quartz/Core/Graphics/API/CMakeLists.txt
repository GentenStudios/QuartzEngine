add_subdirectory(gl)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(apiHeaders
	${currentDir}/Context.hpp
	${currentDir}/BufferLayout.hpp
	${currentDir}/GFXTypes.hpp
	${currentDir}/GraphicsResource.hpp
	${currentDir}/IBuffer.hpp
	${currentDir}/IFramebuffer.hpp
	${currentDir}/IShaderPipeline.hpp
	${currentDir}/ITexture.hpp
	${currentDir}/ITextureArray.hpp
	${currentDir}/IStateManager.hpp

	${glAPIHeaders}

	PARENT_SCOPE
)
