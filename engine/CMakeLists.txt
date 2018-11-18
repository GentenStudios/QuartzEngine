cmake_minimum_required(VERSION 3.0)

project(Phoenix_Engine)

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(header_dir ${PROJECT_SOURCE_DIR}/include)

unset(engineSources CACHE)
unset(engineHeaders CACHE)

add_subdirectory(include)
add_subdirectory(src)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../third_party)
set(include_dirs
    ${dependencies}/SDL2/include
    ${dependencies}/glew/include
    ${dependencies}/stb_image/
	${dependencies}/inih
    ${header_dir}
)

set(libraries SDL2-static SDL2main glew_s)

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
add_library(${PROJECT_NAME} STATIC ${engineSources} ${engineHeaders})
target_link_libraries(${PROJECT_NAME} ${libraries})
target_include_directories(${PROJECT_NAME} PUBLIC ${include_dirs})

foreach(FILE ${engineSources}) 
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    string(REPLACE "/" "\\" GROUP "${GROUP}")

    set(GROUP "Source Files${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

foreach(FILE ${engineHeaders})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    string(REPLACE "/" "\\" GROUP "${GROUP}")

    set(GROUP "Header Files${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()
