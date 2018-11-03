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
    ${dependencies}/SDL2/include
    ${dependencies}/glew/include
    ${dependencies}/../engine/include
)

set(libraries
    Phoenix_Engine
)

if(WIN32)
    set(libraries
        ${libraries}
        imm32.lib
        ole32.lib
        oleaut32.lib
        opengl32.lib
        version.lib
        winmm.lib
        )
endif()

set(AssetsPath ${CMAKE_CURRENT_SOURCE_DIR}/../assets)

file(GLOB shaders ${AssetsPath}/shaders/*.vert ${AssetsPath}/shaders/*.frag)
file(GLOB scripts ${AssetsPath}/scripts/*.wren)
file(GLOB images ${AssetsPath}/images/*.png)

add_custom_target(Phoenix_Client-Assets
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${AssetsPath} ${CMAKE_CURRENT_BINARY_DIR}/assets
				   SOURCES ${shaders} ${scripts} ${images}
)


add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})

add_dependencies(${PROJECT_NAME} Phoenix_Client-Assets)
