cmake_minimum_required(VERSION 3.0)

project(Quartz)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/Build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/Build/lib)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Quartz)
add_subdirectory(QuartzSandbox)
add_subdirectory(Phoenix)