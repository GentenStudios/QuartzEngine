cmake_minimum_required(VERSION 3.0)

project(Quartz)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Quartz)
add_subdirectory(QuartzSandbox)
add_subdirectory(Sandbox)
