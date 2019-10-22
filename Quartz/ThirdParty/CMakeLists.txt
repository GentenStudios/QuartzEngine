cmake_minimum_required(VERSION 3.0)

option(LIBC "..." ON)

project(QuartzDependencies)

set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)

add_subdirectory(glad)
add_subdirectory(SDL2)
add_subdirectory(imgui)
add_subdirectory(sol2)
add_subdirectory(luajit)

# stop SDL trying to control our main function.
add_definitions(-DSDL_MAIN_HANDLED)

set_target_properties(glad imgui PROPERTIES FOLDER QuartzDependencies)
set_target_properties(SDL2main SDL2-static uninstall PROPERTIES FOLDER QuartzDependencies/sdl2)
