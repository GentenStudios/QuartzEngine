cmake_minimum_required(VERSION 3.0)

project(Pheonix_Engine)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include)

set(sources
    ${source_dir}/engine.cpp
    ${source_dir}/utils/logging.cpp
)

set(headers
    ${header_dir}/engine/common.hpp
    ${header_dir}/engine/os.hpp
    
    ${header_dir}/engine/engine.hpp
    
    ${header_dir}/engine/utils/logging.hpp
)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

set(include_dirs
    ${dependencies}/glm
    ${header_dir}
)

set(libraries
    
)

# Link the library
set(LIBRARY_OUTPUT_PATH ../../COMPILE/lib)

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})
#add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})

