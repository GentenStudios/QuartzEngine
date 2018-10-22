cmake_minimum_required(VERSION 3.0)

project(Phoenix_Engine)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include)

set(mathSrc
    ${source_dir}/math/Vector3.cpp
    ${source_dir}/math/Matrix4x4.cpp
    ${source_dir}/math/Vector2.cpp	
)

set(mathHeaders
    ${header_dir}/engine/math/Vector3.hpp
    ${header_dir}/engine/math/Matrix4x4.hpp
    ${header_dir}/engine/math/MathUtils.hpp
    ${header_dir}/engine/math/Vector2.hpp	
)

set(platformSrc
	${source_dir}/SDL/SDLWindow.cpp
    ${source_dir}/graphics/IWindow.cpp
)

set(platformHeaders
	${header_dir}/engine/SDL/SDLWindow.hpp
    ${header_dir}/engine/graphics/IWindow.hpp
    ${header_dir}/engine/graphics/Context.hpp
    ${header_dir}/engine/os.hpp
)

set(graphicsHeaders
	${header_dir}/engine/graphics/opengl/opengl.hpp
	${header_dir}/engine/graphics/opengl/VertexArray.hpp
	${header_dir}/engine/graphics/opengl/VertexBuffer.hpp
	${header_dir}/engine/graphics/opengl/VertexAttrib.hpp
	${header_dir}/engine/graphics/opengl/ShaderPipeline.hpp
)

set(graphicsSrc
	${source_dir}/graphics/opengl/VertexArray.cpp
	${source_dir}/graphics/opengl/VertexBuffer.cpp
    ${source_dir}/graphics/opengl/ShaderPipeline.cpp
)

set(voxelsHeaders
    ${header_dir}/engine/voxels/Block.hpp
    ${header_dir}/engine/voxels/MapBlock.hpp 
	${header_dir}/engine/voxels/Chunk.hpp

    ${header_dir}/engine/entities/Item.hpp
    ${header_dir}/engine/entities/ItemInstance.hpp
)

set(voxelsSrc
    ${source_dir}/voxels/Block.cpp
    ${source_dir}/voxels/MapBlock.cpp

    ${source_dir}/entities/Item.cpp
    ${source_dir}/entities/ItemInstance.cpp
)

set(utilSrc
    ${source_dir}/utils/logging.cpp
)

set(utilHeaders
    ${header_dir}/engine/utils/logging.hpp
)

set(commonHeaders
    ${header_dir}/engine/common.hpp
    ${header_dir}/engine/types.hpp
)

set(sources
	${graphicsSrc}
	${mathSrc}
	${platformSrc}
	${utilSrc}
	${voxelsSrc}
)

set(headers
	${commonHeaders}
	${graphicsHeaders}
	${mathHeaders}
	${platformHeaders}
	${utilHeaders}
	${voxelsHeaders}
)

source_group("Source Files\\Math" FILES ${mathSrc})
source_group("Header Files\\Math" FILES ${mathHeaders})

source_group("Source Files\\Platform" FILES ${platformSrc})
source_group("Header Files\\Platform" FILES ${platformHeaders})

source_group("Source Files\\Graphics" FILES ${graphicsSrc})
source_group("Header Files\\Graphics" FILES ${graphicsHeaders})

source_group("Source Files\\Utils" FILES ${utilSrc})
source_group("Header Files\\Utils" FILES ${utilHeaders})

source_group("Source Files\\Voxels" FILES ${voxelsSrc})
source_group("Header Files\\Voxels" FILES ${voxelsHeaders})

source_group("Header Files\\Common" FILES ${commonHeaders})

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

