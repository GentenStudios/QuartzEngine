cmake_minimum_required(VERSION 3.0)

project(QuartzEngine LANGUAGES CXX)

include(CMakePCH)

add_subdirectory(Include)
add_subdirectory(Source)

add_library(${PROJECT_NAME} STATIC ${engineSources} ${engineHeaders})
add_precompiled_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/Include/Quartz/QuartzPCH.hpp ${CMAKE_CURRENT_LIST_DIR}/Source/QuartzPCH.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2-static SDL2main liblua)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../ThirdParty)
target_include_directories(${PROJECT_NAME} PUBLIC 
	${dependencies}/sol2/include
	${dependencies}/stb_image
	${CMAKE_CURRENT_LIST_DIR}/Include
)

if(WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE imm32.lib ole32.lib oleaut32.lib opengl32.lib version.lib winmm.lib)
endif()

if(UNIX AND NOT APPLE)
	find_package(X11 REQUIRED)
	find_package(Threads REQUIRED)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES} GL)
endif()


foreach(FILE ${engineSources}) 
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    string(REPLACE "/" "\\" GROUP "${GROUP}")
	string(REPLACE "Source" "" GROUP "${GROUP}")

    set(GROUP "Source Files${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

foreach(FILE ${engineHeaders})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    string(REPLACE "/" "\\" GROUP "${GROUP}")
	string(REPLACE "Include" "" GROUP "${GROUP}")

    set(GROUP "Header Files${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()
