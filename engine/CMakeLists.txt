cmake_minimum_required(VERSION 3.0)

project(Pheonix_Engine)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include/engine)

set(sources
    ${source_dir}/engine.cpp
)

set(headers
    ${header_dir}/engine.hpp
)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

set(include_dirs
    ${dependencies}/glm
    ${header_dir}/../
)

set(libraries
    
)

# Link the library
set(LIBRARY_OUTPUT_PATH ../../COMPILE/lib)

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})

