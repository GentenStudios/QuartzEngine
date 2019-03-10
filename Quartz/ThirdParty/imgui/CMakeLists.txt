cmake_minimum_required(VERSION 3.0)
project(imgui)

set(cdir ${CMAKE_CURRENT_LIST_DIR})

set(source
	${cdir}/src/imgui.cpp
	${cdir}/src/imgui_demo.cpp
	${cdir}/src/imgui_draw.cpp
	${cdir}/src/imgui_impl_opengl3.cpp
	${cdir}/src/imgui_impl_sdl.cpp
	${cdir}/src/imgui_widgets.cpp
)

set(headers
	${cdir}/include/imgui/imconfig.h
	${cdir}/include/imgui/imgui.h
	${cdir}/include/imgui/imgui_impl_opengl3.h
	${cdir}/include/imgui/imgui_impl_sdl.h
	${cdir}/include/imgui/imgui_internal.h
	${cdir}/include/imgui/imstb_rectpack.h
	${cdir}/include/imgui/imstb_textedit.h
	${cdir}/include/imgui/imstb_truetype.h
)

add_library(${PROJECT_NAME} STATIC ${source} ${headers})
target_include_directories(${PROJECT_NAME} PUBLIC include/imgui ../SDL2/include ../glad/include)
