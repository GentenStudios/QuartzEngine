cmake_minimum_required(VERSION 3.2)
project(luamod)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(vendor/luajit)
set_target_properties(buildvm liblua luajit minilua wluajit PROPERTIES FOLDER "vendor/luajit")

set(cdir ${CMAKE_CURRENT_LIST_DIR})
file(GLOB source ${cdir}/src/*.cpp)
file(GLOB headers ${cdir}/include/luamod/*.h)

add_library(${PROJECT_NAME} STATIC ${source} ${headers})
target_link_libraries(${PROJECT_NAME} liblua)

include_directories(
    ${cdir}/vendor/luajit/src
    ${cdir}/include
)

file(GLOB scripts ${cdir}/scripts/*.lua)

add_custom_target(scripts_target
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${cdir}/scripts ${CMAKE_CURRENT_BINARY_DIR}/scripts
				   SOURCES ${scripts}
)
source_group("Scripts" FILES ${scripts})

add_dependencies(${PROJECT_NAME} scripts_target)
