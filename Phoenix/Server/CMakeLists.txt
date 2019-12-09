cmake_minimum_required(VERSION 3.0)

project(PhoenixServer)

add_subdirectory(Include)
add_subdirectory(Source)

add_executable(${PROJECT_NAME} ${serverSources} ${serverHeaders})
target_link_libraries(${PROJECT_NAME} PRIVATE Phoenix)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../../Quartz/ThirdParty)
target_include_directories(${PROJECT_NAME} PRIVATE ${dependencies}/SDL2/include ${dependencies}/../Engine/Include ${dependencies}/sol2/include ${dependencies}/lua ${dependencies}/imgui/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../Core/Include)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:liblua>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:liblua>
)
