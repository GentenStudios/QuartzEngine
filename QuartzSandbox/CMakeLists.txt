cmake_minimum_required(VERSION 3.0)

project(quartz-sandbox)

add_subdirectory(Include)
add_subdirectory(Source)
add_subdirectory(Assets)

add_executable(${PROJECT_NAME} ${clientSources} ${clientHeaders})
target_link_libraries(${PROJECT_NAME} PRIVATE quartz-engine)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../Quartz/ThirdParty)
target_include_directories(${PROJECT_NAME} PRIVATE ${dependencies}/SDL2/include ${dependencies}/../Quartz/Engine/include ${dependencies}/luamod/include ${dependencies}/imgui/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include)

add_dependencies(${PROJECT_NAME} quartz-sandbox-assets)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:liblua>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:liblua>
)
