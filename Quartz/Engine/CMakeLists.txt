cmake_minimum_required(VERSION 3.0)

project(QuartzEngine LANGUAGES CXX)

include(CMakePCH)

add_subdirectory(Include)
add_subdirectory(Source)

add_library(${PROJECT_NAME} STATIC ${quartzSources} ${quartzHeaders})
#add_precompiled_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/Include/Quartz/Core/QuartzPCH.hpp ${CMAKE_CURRENT_LIST_DIR}/Source/Core/QuartzPCH.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2-static SDL2main glad luamod imgui)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../ThirdParty)
target_include_directories(${PROJECT_NAME} PUBLIC 
	${dependencies}/SDL2/include 
	${dependencies}/glad/include 
	${dependencies}/stb_image 
	${dependencies}/inih 
	${dependencies}/luamod/include
	${dependencies}/imgui/include
	${dependencies}/entt
	${CMAKE_CURRENT_LIST_DIR}/Include
)

if(WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE imm32.lib ole32.lib oleaut32.lib opengl32.lib version.lib winmm.lib)
endif()

if(UNIX AND NOT APPLE)
	find_package(X11 REQUIRED)
	find_package(Threads REQUIRED)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES} ${X11_Xxf86vm_LIB} GL)
endif()

foreach(FILE ${quartzSources}) 
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    string(REPLACE "/" "\\" GROUP "${GROUP}")
	string(REPLACE "Source" "" GROUP "${GROUP}")

    set(GROUP "Source Files${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

foreach(FILE ${quartzHeaders})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    string(REPLACE "/" "\\" GROUP "${GROUP}")
	string(REPLACE "Include" "" GROUP "${GROUP}")

    set(GROUP "Header Files${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()
