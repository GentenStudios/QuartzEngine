cmake_minimum_required(VERSION 3.0)

project(quartz)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(quartz/third_party)
add_subdirectory(quartz/engine)
add_subdirectory(quartz/client)
