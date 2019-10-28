cmake_minimum_required(VERSION 3.0)

project(Sandbox)

add_subdirectory(Source)

add_executable(${PROJECT_NAME} ${sandboxSources})
target_link_libraries(${PROJECT_NAME} PRIVATE QuartzEngine liblua)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../Quartz/ThirdParty)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${dependencies}/SDL2/include 
    ${dependencies}/../Quartz/Engine/Include 
    ${dependencies}/imgui/include
    ${dependencies}/luajit/src
    ${dependencies}/sol2/include
    ${CMAKE_CURRENT_BINARY_DIR}/../Quartz/ThirdParty/luajit)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:liblua>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:liblua>
)

