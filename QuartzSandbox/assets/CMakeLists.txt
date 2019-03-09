cmake_minimum_required(VERSION 3.0)

project(quartz-sandbox-assets)

set(assetsPath ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB shaders ${assetsPath}/Shaders/*.vert ${assetsPath}/Shaders/*.frag)
file(GLOB scripts ${assetsPath}/Scripts/*.lua)
file(GLOB textures ${assetsPath}/Textures/*.png)

source_group("Shaders" FILES ${shaders})
source_group("Scripts" FILES ${scripts})
source_group("Textures" FILES ${textures})

add_custom_target(${PROJECT_NAME}
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${assetsPath} ${CMAKE_CURRENT_BINARY_DIR}/assets
				   SOURCES ${shaders} ${scripts} ${textures}
)
