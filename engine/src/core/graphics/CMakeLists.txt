set(graphicsSourceDir ${CMAKE_CURRENT_LIST_DIR})

set(openglSources
    ${graphicsSourceDir}/gl/ShaderPipeline.cpp
    ${graphicsSourceDir}/gl/TextureArray.cpp
    ${graphicsSourceDir}/gl/VertexArray.cpp
    ${graphicsSourceDir}/gl/VertexBuffer.cpp
)

set(graphicsSources
    ${graphicsSourceDir}/Camera.cpp
    ${graphicsSourceDir}/IWindow.cpp

	${graphicsSourceDir}/BatchRenderer.cpp
)

source_group("Source Files\\Core\\Graphics" FILES ${graphicsSources})
source_group("Source Files\\Core\\Graphics\\OpenGL" FILES ${openglSources})

set(engineSources
    ${engineSources}
    ${graphicsSources}
    ${openglSources}
    CACHE INTERNAL "Global Engine Sources"
)