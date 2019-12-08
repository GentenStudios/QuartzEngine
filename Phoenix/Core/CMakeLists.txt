cmake_minimum_required(VERSION 3.0)

project(Phoenix)

add_subdirectory(Include)
add_subdirectory(Source)

add_library(${PROJECT_NAME} STATIC ${phoenixSources} ${phoenixHeaders})
target_link_libraries(${PROJECT_NAME} PRIVATE QuartzEngine)

set(dependencies ${CMAKE_CURRENT_LIST_DIR}/../../Quartz/ThirdParty)
target_include_directories(${PROJECT_NAME} PRIVATE ${dependencies}/../Engine/Include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include)

foreach(FILE ${phoenixSources}) 
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    string(REPLACE "/" "\\" GROUP "${GROUP}")
	string(REPLACE "Source" "" GROUP "${GROUP}")

    set(GROUP "Source Files${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

foreach(FILE ${phoenixHeaders})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    string(REPLACE "/" "\\" GROUP "${GROUP}")
	string(REPLACE "Include" "" GROUP "${GROUP}")

    set(GROUP "Header Files${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()
