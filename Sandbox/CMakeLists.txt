cmake_minimum_required(VERSION 3.0)

project(Sandbox)

add_subdirectory(Source)

add_executable(${PROJECT_NAME} ${sandboxSources})
target_link_libraries(${PROJECT_NAME} PRIVATE QuartzEngine)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../Quartz/ThirdParty)
target_include_directories(${PROJECT_NAME} PRIVATE ${dependencies}/SDL2/include ${dependencies}/../Quartz/Engine/Include ${dependencies}/luamod/include ${dependencies}/imgui/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include)
