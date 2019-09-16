cmake_minimum_required(VERSION 3.0)

project(Quartz)

set(CMAKE_CXX_STANDARD 11)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_subdirectory(Quartz)
add_subdirectory(QuartzSandbox)
add_subdirectory(Pheonix)