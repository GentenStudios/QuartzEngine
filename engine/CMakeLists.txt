cmake_minimum_required(VERSION 3.0)

project(Phoenix_Engine)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include)

set(sources
    ${source_dir}/engine.cpp
    ${source_dir}/utils/logging.cpp

    ${source_dir}/math/vector3.cpp
    ${source_dir}/math/matrix4x4.cpp
    ${source_dir}/math/vector2.cpp

    ${source_dir}/graphics/window.cpp

    ${source_dir}/graphics/opengl/vertexArray.cpp
    ${source_dir}/graphics/opengl/buffer.cpp
    ${source_dir}/graphics/opengl/texture.cpp
    ${source_dir}/graphics/opengl/shader.cpp

    ${source_dir}/camera.cpp
  	
    ${source_dir}/imgui.cpp
    
    ${source_dir}/voxels/block.cpp
#    ${source_dir}/voxels/chunk.cpp
    ${source_dir}/voxels/mapblock.cpp
)

set(headers
    ${header_dir}/engine/common.hpp
    ${header_dir}/engine/os.hpp
    ${header_dir}/engine/engine.hpp
    
    ${header_dir}/engine/math/vector3.hpp
    ${header_dir}/engine/math/matrix4x4.hpp
    ${header_dir}/engine/math/mathutils.hpp
    ${header_dir}/engine/math/vector2.hpp

    ${header_dir}/engine/utils/logging.hpp

    ${header_dir}/engine/graphics/window.hpp
    
    ${header_dir}/engine/graphics/opengl/glTypes.hpp
    ${header_dir}/engine/graphics/opengl/vertexArray.hpp
    ${header_dir}/engine/graphics/opengl/vertexAttrib.hpp
    ${header_dir}/engine/graphics/opengl/buffer.hpp
    ${header_dir}/engine/graphics/opengl/shader.hpp
    ${header_dir}/engine/graphics/opengl/texture.hpp


    ${header_dir}/engine/camera.hpp
	  ${header_dir}/engine/imgui.hpp

#    ${header_dir}/engine/voxels/chunk.hpp
     ${header_dir}/engine/voxels/block.hpp
     ${header_dir}/engine/voxels/mapblock.hpp 
)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)

set(include_dirs
    ${dependencies}/glfw/include
    ${dependencies}/glew/include
	${dependencies}/ImGUI
    ${header_dir}
)

set(libraries
    glfw
    glew_s
	ImGui
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

