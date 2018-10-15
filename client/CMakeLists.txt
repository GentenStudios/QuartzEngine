cmake_minimum_required(VERSION 3.0)

project(Pheonix_Client)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include/client)
set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

set(sources
    ${source_dir}/main.cpp
    ${source_dir}/chunk.cpp
    ${source_dir}/textures.cpp

)

set(headers
    ${header_dir}/client.hpp
    ${header_dir}/chunk.hpp
    ${header_dir}/textures.hpp

    ${dependencies}/stb_image/stb_image/stb_image.h
)


set(include_dirs
    ${dependencies}/glm
    ${dependencies}/glfw/include
    ${dependencies}/glew/include
    ${dependencies}/stb_image/
    ${header_dir}/../
    ${source_dir}/../../engine/include
)

set(libraries
    Pheonix_Engine
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

# Link the executable
set(EXECUTABLE_OUTPUT_PATH ../../COMPILE/bin)

add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})

