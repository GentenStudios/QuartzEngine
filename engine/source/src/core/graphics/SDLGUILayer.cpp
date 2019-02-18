#include <quartz/core/graphics/SDLGUILayer.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace qz::gfx;

void SDLGUILayer::init(SDL_Window* window, SDL_GLContext* ctx)
{
	m_window = window;
	m_context = ctx;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, ctx); 
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void SDLGUILayer::startFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
}

void SDLGUILayer::endFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void SDLGUILayer::pollEvents(SDL_Event* e)
{
	ImGui_ImplSDL2_ProcessEvent(e);
}
