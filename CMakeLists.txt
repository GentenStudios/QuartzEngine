cmake_minimum_required(VERSION 3.0)

project(quartz)

set(CMAKE_CXX_STANDARD 11)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakePCHCompiler)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(third_party)
add_subdirectory(engine)
add_subdirectory(sandbox)
