# Say that VERSION 3.0 of CMake is the minumum required.
cmake_minimum_required( VERSION 3.0 )

# Set the Project name.
project( Pheonix-Dependencies )

# Add the subdirectories for all our dependencies
# add_subdirectory( directory_name_here )
# for example: add_subdirectory( glew )

add_subdirectory( wren )
add_subdirectory( glfw )
#add_subdirectory( glew/build/cmake )
