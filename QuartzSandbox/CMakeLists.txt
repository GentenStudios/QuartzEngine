cmake_minimum_required(VERSION 3.0)

project(quartz-sandbox)

add_subdirectory(source/include)
add_subdirectory(source/src)

set(assetsPath ${CMAKE_CURRENT_SOURCE_DIR}/assets)

file(GLOB shaders ${assetsPath}/shaders/*.vert ${assetsPath}/shaders/*.frag)
file(GLOB scripts ${assetsPath}/scripts/*.lua)
file(GLOB images ${assetsPath}/images/*.png)

source_group("Shaders" FILES ${shaders})
source_group("Scripts" FILES ${scripts})
source_group("Images" FILES ${images})

add_custom_target(quartz-sandbox-assets
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${assetsPath} ${CMAKE_CURRENT_BINARY_DIR}/assets
				   SOURCES ${shaders} ${scripts} ${images}
)

add_executable(${PROJECT_NAME} ${clientSources} ${clientHeaders})
target_link_libraries(${PROJECT_NAME} PRIVATE quartz-engine)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)
target_include_directories(${PROJECT_NAME} PRIVATE ${dependencies}/SDL2/include ${dependencies}/glew/include ${dependencies}/../engine/include ${dependencies}/luamod/include ${dependencies}/imgui/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/source/include)

add_dependencies(${PROJECT_NAME} quartz-sandbox-assets)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:liblua>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:liblua>
)
