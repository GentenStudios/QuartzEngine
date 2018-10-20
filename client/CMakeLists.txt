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
    ${dependencies}/../engine/include
	${dependencies}/glew/include
)

set(libraries
    glew_s
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

# Link the executable
set(EXECUTABLE_OUTPUT_PATH ../../COMPILE/bin)

add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${libraries})
include_directories(${include_dirs})
