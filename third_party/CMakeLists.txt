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

set_target_properties(glew_s glew SDL2-static SDL2main SDL2 uninstall PROPERTIES FOLDER third_party)
