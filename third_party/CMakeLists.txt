# Say that VERSION 3.0 of CMake is the minumum required.
cmake_minimum_required(VERSION 3.0)

option(LIBC "..." ON)

# Set the Project name.
project(Pheonix-Dependencies)

# Add the subdirectories for all our dependencies
# add_subdirectory( directory_name_here )
# for example: add_subdirectory( glew )

add_subdirectory(glew/build/cmake)
add_subdirectory(SDL2)
add_subdirectory(luamod)

set_target_properties(buildvm liblua luajit minilua wluajit PROPERTIES FOLDER third_party/lua/luajit)
set_target_properties(luamod scripts_target PROPERTIES FOLDER third_party/lua)
set_target_properties(glew_s glew PROPERTIES FOLDER third_party/glew)
set_target_properties(SDL2main SDL2 SDL2-static uninstall PROPERTIES FOLDER third_party/sdl2)
