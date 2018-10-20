cmake_minimum_required(VERSION 3.0)

project(Phoenix_Client)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include/client)
set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

set(sources
    ${source_dir}/main.cpp
)

set(headers
)


set(include_dirs
)

set(libraries
    Phoenix_Engine
)

# Link the executable
set(EXECUTABLE_OUTPUT_PATH ../../COMPILE/bin)

add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})
