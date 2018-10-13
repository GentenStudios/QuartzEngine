cmake_minimum_required(VERSION 3.0)

project(Pheonix_Engine)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include)

set(sources
    ${source_dir}/engine.cpp
    ${source_dir}/utils/logging.cpp

    ${source_dir}/graphics/window.cpp

    ${source_dir}/graphics/opengl/vertexArray.cpp
    ${source_dir}/graphics/opengl/buffer.cpp
)

set(headers
    ${header_dir}/engine/common.hpp
    ${header_dir}/engine/os.hpp
    ${header_dir}/engine/engine.hpp
    
    ${header_dir}/engine/utils/logging.hpp

    ${header_dir}/engine/graphics/window.hpp

    ${header_dir}/engine/graphics/opengl/glTypes.hpp
    ${header_dir}/engine/graphics/opengl/vertexArray.hpp
    ${header_dir}/engine/graphics/opengl/buffer.hpp
    ${header_dir}/engine/graphics/opengl/vertexAttrib.hpp
    ${header_dir}/engine/graphics/opengl/texture.hpp
)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

set(include_dirs
    ${dependencies}/glm
    ${dependencies}/glfw/include
    ${dependencies}/glew/include
    ${header_dir}
)

set(libraries
    glfw
    glew_s
)

if(WIN32)
    set(libraries
        ${libraries}
        OpenGL32.lib
    )
endif()

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    find_package(Threads REQUIRED)
    set(libraries
        ${libraries}
        ${X11_LIBRARIES}
        ${X11_Xxf86vm_LIB}
        GL
        )
endif()

# Link the library
set(LIBRARY_OUTPUT_PATH ../../COMPILE/lib)

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})
#add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})

