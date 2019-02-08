set(graphicsSourceDir ${CMAKE_CURRENT_LIST_DIR})

set(openglSources
	${graphicsSourceDir}/gl/ShaderPipeline.cpp
	${graphicsSourceDir}/gl/TextureArray.cpp
	${graphicsSourceDir}/gl/VertexArray.cpp
	${graphicsSourceDir}/gl/VertexBuffer.cpp
)

set(graphicsSources
	${openglSources}

	${graphicsSourceDir}/Camera.cpp
	${graphicsSourceDir}/IWindow.cpp

	${graphicsSourceDir}/BatchRenderer.cpp
	${graphicsSourceDir}/Renderer2D.cpp

	PARENT_SCOPE
)