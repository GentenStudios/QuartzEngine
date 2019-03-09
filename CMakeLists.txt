cmake_minimum_required(VERSION 3.0)

project(quartz)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(third_party)
add_subdirectory(engine)
add_subdirectory(sandbox)
