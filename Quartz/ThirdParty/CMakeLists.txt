cmake_minimum_required(VERSION 3.0)

option(LIBC "..." ON)

project(QuartzDependencies)

set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)

add_subdirectory(glad)
add_subdirectory(SDL2)
add_subdirectory(imgui)

# stop SDL trying to control our main function.
add_definitions(-DSDL_MAIN_HANDLED)

# FIX: @ThirdParty @ImGUI
#   Properly specify which interface (ie. glad) to use with ImGui_ImplOpenGL3.h
#   otherwise it guesses which interface to use and may throw a linker error.
#
# NOTE:
#   Should replace -> https://cmake.org/cmake/help/latest/command/add_definitions.html
#   with this -> https://cmake.org/cmake/help/latest/command/add_compile_definitions.html#command:add_compile_definitions
#   if we migrate / update to the latest version of cmake.
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

set_target_properties(glad imgui PROPERTIES FOLDER QuartzDependencies)
set_target_properties(SDL2main SDL2-static uninstall PROPERTIES FOLDER QuartzDependencies/sdl2)
