cmake_minimum_required(VERSION 3.0)

project(Pheonix_Launcher)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include/launcher)

set(sources
    ${source_dir}/main.cpp
)

set(headers
    ${header_dir}/launcher.hpp
)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

set(include_dirs#
    ${header_dir}/../
    ${CMAKE_CURRENT_LIST_DIR}/../engine/include
)

set(libraries
    Pheonix_Engine
)

# Link the executable
set(EXECUTABLE_OUTPUT_PATH ../../COMPILE/bin)

add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})

