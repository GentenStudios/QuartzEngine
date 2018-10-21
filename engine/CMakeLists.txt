cmake_minimum_required(VERSION 3.0)

project(Phoenix_Engine)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include)

set(sources
    ${source_dir}/utils/logging.cpp

    ${source_dir}/math/Vector3.cpp
    ${source_dir}/math/Matrix4x4.cpp
    ${source_dir}/math/Vector2.cpp

    ${source_dir}/SDL/SDLWindow.cpp

    ${source_dir}/graphics/IWindow.cpp

	${source_dir}/graphics/opengl/VertexArray.cpp
	${source_dir}/graphics/opengl/ShaderPipeline.cpp
)

set(headers
    ${header_dir}/engine/common.hpp
    ${header_dir}/engine/os.hpp
    ${header_dir}/engine/types.hpp

    ${header_dir}/engine/math/Vector3.hpp
    ${header_dir}/engine/math/Matrix4x4.hpp
    ${header_dir}/engine/math/MathUtils.hpp
    ${header_dir}/engine/math/Vector2.hpp

    ${header_dir}/engine/utils/logging.hpp

    ${header_dir}/engine/SDL/SDLWindow.hpp

    ${header_dir}/engine/graphics/IWindow.hpp
    ${header_dir}/engine/graphics/Context.hpp

	${header_dir}/engine/graphics/opengl/opengl.hpp
	${header_dir}/engine/graphics/opengl/VertexArray.hpp
	${header_dir}/engine/graphics/opengl/VertexBuffer.hpp
	${header_dir}/engine/graphics/opengl/ShaderPipeline.hpp
)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

set(include_dirs
    ${dependencies}/SDL2/include
    ${dependencies}/glew/include
    ${header_dir}
)

set(libraries
    SDL2-static
    SDL2main
    glew_s
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

