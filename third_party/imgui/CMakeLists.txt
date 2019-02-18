cmake_minimum_required(VERSION 3.0)
project(imgui)

file(GLOB source src/*.cpp)
file(GLOB headers include/*.h)

add_library(${PROJECT_NAME} STATIC ${source} ${headers})
target_include_directories(${PROJECT_NAME} PUBLIC include/imgui ../SDL2/include ../glad/include)
