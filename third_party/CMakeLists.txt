cmake_minimum_required(VERSION 3.0)

option(LIBC "..." ON)

project(quartz-dependencies)

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/luamod/include)
	message("It seems like the Git Submodules have not been initialised and cloned, they will now be initialised and cloned as required.")
	execute_process(COMMAND git submodule update --init
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
endif()

add_subdirectory(glad)
add_subdirectory(SDL2)
add_subdirectory(luamod)
add_subdirectory(imgui)

set_target_properties(buildvm liblua luajit minilua PROPERTIES FOLDER quartz-dependencies/lua/luajit)

if(WIN32)
    set_target_properties(wluajit PROPERTIES FOLDER quartz-dependencies/lua/luajit)
endif()

set_target_properties(luamod luamod_tests PROPERTIES FOLDER quartz-dependencies/lua)
set_target_properties(SDL2main SDL2 SDL2-static uninstall PROPERTIES FOLDER quartz-dependencies/sdl2)
set_target_properties(glad imgui PROPERTIES FOLDER quartz-dependencies)
