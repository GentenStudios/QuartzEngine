cmake_minimum_required(VERSION 3.0)

project(Phoenix_Client)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include/client)
set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

unset(clientSources CACHE)
unset(clientHeaders CACHE)

add_subdirectory(include)
add_subdirectory(src)

set(include_dirs ${dependencies}/SDL2/include ${dependencies}/../engine/include ${dependencies}/luamod/include ${CMAKE_CURRENT_LIST_DIR}/include)
set(libraries Phoenix_Engine)

set(AssetsPath ${CMAKE_CURRENT_SOURCE_DIR}/../assets)

file(GLOB shaders ${AssetsPath}/shaders/*.vert ${AssetsPath}/shaders/*.frag)
file(GLOB scripts ${AssetsPath}/scripts/*.lua)
file(GLOB images ${AssetsPath}/images/*.png)

source_group("Shaders" FILES ${shaders})
source_group("Scripts" FILES ${scripts})
source_group("Images" FILES ${images})
add_custom_target(Phoenix_Client-Assets
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${AssetsPath} ${CMAKE_CURRENT_BINARY_DIR}/assets
				   SOURCES ${shaders} ${scripts} ${images}
)

add_executable(${PROJECT_NAME} ${clientSources} ${clientHeaders})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:liblua>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:liblua>
)

add_dependencies(${PROJECT_NAME} Phoenix_Client-Assets)
