cmake_minimum_required(VERSION 3.0)

project(QuartzDependencies)

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/SDL2/include)
	message("It seems like the Git Submodules have not been initialised and cloned, they will now be initialised and cloned as required.")
	execute_process(COMMAND git submodule update --init
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
endif()

set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)

add_subdirectory(SDL2)
add_subdirectory(sol2)
add_subdirectory(lua)
add_subdirectory(bgfx.cmake)

# stop SDL trying to control our main function.
add_definitions(-DSDL_MAIN_HANDLED)

set_target_properties(SDL2main SDL2-static uninstall PROPERTIES FOLDER QuartzDependencies/sdl2)
set_target_properties(liblua lua PROPERTIES FOLDER QuartzDependencies/lua)
set_target_properties(astc astc-codec dear-imgui edtaa3 etc1 etc2 fcpp glcpp glslang glsl-optimizer iqa mesa meshoptimizer nvtt pvrtc spirv-cross spirv-tools squish PROPERTIES FOLDER QuartzDependencies/bgfx/third-party)
set_target_properties(example-common examples PROPERTIES FOLDER QuartzDependencies/bgfx/examples)
set_target_properties(geometryc shaderc texturec texturev tools PROPERTIES FOLDER QuartzDependencies/bgfx/tools)
set_target_properties(bgfx bimg bx PROPERTIES FOLDER QuartzDependencies/bgfx)
