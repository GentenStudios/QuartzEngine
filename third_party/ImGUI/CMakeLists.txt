project(ImGui)

set(src
	imgui.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	examples/imgui_impl_opengl3.cpp
	examples/imgui_impl_glfw.cpp
)

set(headers
	examples/imgui_impl_opengl3.h
	examples/imgui_impl_glfw.h
	imconfig.h
	imgui.h
	imgui_internal.h
	stb_rect_pack.h
	stb_textedit.h
	stb_truetype.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../glew/include
	${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include
)

add_library(ImGui ${src} ${headers})

target_link_libraries(ImGui glew_s glfw)