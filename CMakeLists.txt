# Say that VERSION 3.0 of CMake is the minumum required.
cmake_minimum_required(VERSION 3.0)

# Set the Project name.
project(Project-Phoenix)

# Make CMake use folders. (makes things slightly tidier in the future)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add the subdirectory for all our Third Party dependencies
add_subdirectory(third_party)

# Add the subdirectory for our Engine.
add_subdirectory(engine)

# Add the subdirectory for our Client.
add_subdirectory(client)
