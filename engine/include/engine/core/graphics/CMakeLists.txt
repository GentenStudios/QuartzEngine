set(graphicsIncludeDir ${CMAKE_CURRENT_LIST_DIR})

set(openglHeaders
    ${graphicsIncludeDir}/gl/Context.hpp
    ${graphicsIncludeDir}/gl/GLDebug.hpp
    ${graphicsIncludeDir}/gl/GLEnums.hpp
    ${graphicsIncludeDir}/gl/ShaderPipeline.hpp
    ${graphicsIncludeDir}/gl/TextureArray.hpp
    ${graphicsIncludeDir}/gl/VertexArray.hpp
    ${graphicsIncludeDir}/gl/VertexAttrib.hpp
    ${graphicsIncludeDir}/gl/VertexBuffer.hpp
)

set(graphicsHeaders
    ${graphicsIncludeDir}/Camera.hpp
    ${graphicsIncludeDir}/IWindow.hpp

	${graphicsIncludeDir}/BatchRenderer.hpp
	${graphicsIncludeDir}/Renderer2D.hpp
)

source_group("Header Files\\Core\\Graphics" FILES ${graphicsHeaders})
source_group("Header Files\\Core\\Graphics\\OpenGL" FILES ${openglHeaders})

set(engineHeaders
    ${engineHeaders}
    ${graphicsHeaders}
    ${openglHeaders}
    CACHE INTERNAL "Global Engine Headers"
)