cmake_minimum_required(VERSION 3.0)

project(QuartzSandbox)

add_subdirectory(Include)
add_subdirectory(Source)
add_subdirectory(assets)

add_executable(${PROJECT_NAME} ${sandboxSources} ${sandboxHeaders})
target_link_libraries(${PROJECT_NAME} PRIVATE QuartzEngine)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../Quartz/ThirdParty)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${dependencies}/SDL2/include 
    ${dependencies}/../Quartz/Engine/Include 
    ${dependencies}/imgui/include
    ${dependencies}/luajit/include
    ${dependencies}/sol2/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include)

add_dependencies(${PROJECT_NAME} QuartzSandboxAssets)
