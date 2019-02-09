set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(openglHeaders
    ${currentDir}/gl/Context.hpp
    ${currentDir}/gl/GLDebug.hpp
    ${currentDir}/gl/GLEnums.hpp
    ${currentDir}/gl/ShaderPipeline.hpp
    ${currentDir}/gl/TextureArray.hpp
    ${currentDir}/gl/VertexArray.hpp
    ${currentDir}/gl/VertexAttrib.hpp
    ${currentDir}/gl/VertexBuffer.hpp
)

set(graphicsHeaders
	${openglHeaders}

	${currentDir}/Camera.hpp
	${currentDir}/IWindow.hpp

	${currentDir}/BatchRenderer.hpp
	${currentDir}/Renderer2D.hpp

	PARENT_SCOPE
)
