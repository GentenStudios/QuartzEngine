cmake_minimum_required(VERSION 3.0)

project(Pheonix_Server)

set(source_dir ${PROJECT_SOURCE_DIR}/source/src)
set(header_dir ${PROJECT_SOURCE_DIR}/source/include)

set(sources
    ${source_dir}/main.cpp
)

set(headers
    ${header_dir}/server.hpp
)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

set(include_dirs
    ${dependencies}/glm
    ${source_dir}/../include
    ${CMAKE_CURRENT_LIST_DIR}/../engine/source/include
)

set(libraries
    Pheonix_Engine
)

# Link the executable
set(EXECUTABLE_OUTPUT_PATH ../../COMPILE/bin)

add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})

