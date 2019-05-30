
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#include <Sandbox/Sandbox.hpp>
#include <Quartz.hpp>

#include <Quartz/Graphics/RHI/IRenderDevice.hpp>
#include <Quartz/Graphics/RHI/OpenGL/GLRenderDevice.hpp>
#include <imgui/imgui.h>

#include <Quartz/Graphics/ForwardMeshRenderer.hpp>
#include <Quartz/Voxels/Blocks.hpp>
#include <Quartz/Graphics/Camera.hpp>
#include <Quartz/Graphics/ImGuiExtensions.hpp>

using namespace sandbox;
using namespace qz;

Sandbox::Sandbox()
{
	m_appRequirements = new ApplicationRequirements();
	m_appRequirements->windowTitle = "Quartz Sandbox";
	m_appRequirements->windowWidth = 1280;
	m_appRequirements->windowHeight = 720;

	m_appRequirements->logFilePath = "Sandbox.log";
	m_appRequirements->logVerbosity = utils::LogVerbosity::DEBUG;
}

static void showHintUi()
{
	const float DISTANCE = 10.0f;
	const int corner = 1;
	static bool p_open = true;

	ImGuiIO& io = ImGui::GetIO();

	ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

	ImGui::SetNextWindowBgAlpha(0.3f);

	if (ImGui::Begin("Debug Overlay Hint", &p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::Text("Press K to toggle developer tools!");
	}

	ImGui::End();
}

void Sandbox::run()
{
	using namespace gfx::rhi;
	using namespace gfx::rhi::gl;

	gfx::IWindow* window = m_appData->window;
	window->setVSync(false);
	window->registerEventListener([&](qz::events::Event& e) { onEvent(e); });

	voxels::BlockRegistery* blocksRegistery = voxels::BlockRegistery::get();
	blocksRegistery->registerBlock({"Air", "core:air", voxels::BlockTypeCategory::AIR});

	voxels::BlockType* dirtBlockType = blocksRegistery->registerBlock({"Dirt", "core:dirt", voxels::BlockTypeCategory::SOLID});

	m_renderDevice = new GLRenderDevice();
	m_renderDevice->create();

	// #todo find some way of returning the sprite ID on creation (instead of having to do a lookup with the filepath again)
	voxels::BlockTextureAtlas atlas(16, 16);
	atlas.addTextureFile("assets/textures/grass_top.png");
	atlas.addTextureFile("assets/textures/dirt.png");
	atlas.addTextureFile("assets/textures/grass_side.png");
	atlas.patch();

	// #todo (fix) temporary == remove.
	dirtBlockType->textures.top =
			dirtBlockType->textures.bottom =
			dirtBlockType->textures.left =
			dirtBlockType->textures.right =
			dirtBlockType->textures.front =
			dirtBlockType->textures.back =
			atlas.getSpriteIDFromFilepath("assets/textures/dirt.png");

	auto grassTextureCoordinates = atlas.getSpriteIDFromFilepath("assets/textures/grass_top.png");

	RectAABB uvs = atlas.getSpriteFromID(dirtBlockType->textures.front);

	gfx::Mesh mesh(6);
	mesh.addVertex({{0.f, 0.f, 1.0f}, uvs.topLeft });
	mesh.addVertex({{0.f, 1.f, 1.0f}, uvs.bottomLeft });
	mesh.addVertex({{1.0f, 1.0f, 1.0f}, uvs.bottomRight });

	mesh.addVertex({{1.f, 1.f, 1.0f}, uvs.bottomRight });
	mesh.addVertex({{1.f, 0.f, 1.0f}, uvs.topRight });
	mesh.addVertex({{0.0f, 0.0f, 1.0f}, uvs.topLeft });

	gfx::ForwardMeshRenderer renderer(m_renderDevice);
	renderer.create();

	renderer.submitMesh(&mesh);

	m_camera = new gfx::FPSCamera(window);
	m_camera->setProjection(Matrix4x4::perspective(1280.f / 720.f, 90.f, 100.f, 0.1f));
	renderer.setProjectionMatrix(m_camera->getProjection());


	TextureHandle texture = m_renderDevice->createTexture(atlas.getPatchedTetureData(), atlas.getPatchedTextureWidth(), atlas.getPatchedTextureHeight());
	m_renderDevice->setTexture(texture, 0);

	std::size_t fpsLastTime = SDL_GetTicks();
	int fpsCurrent = 0;
	int fpsFrames = 0;

	float last = static_cast<float>(SDL_GetTicks());
	int t = 0;
	int dtSampleRate = 60;
	bool pauseDt = false;
	bool vsync = false;
	bool fullscreen = false;
	while (window->isRunning())
	{
		fpsFrames++;
		if (fpsLastTime < SDL_GetTicks() - 1000)
		{
			fpsLastTime = SDL_GetTicks();
			fpsCurrent = fpsFrames;
			fpsFrames = 0;
		}

		const float now = static_cast<float>(SDL_GetTicks());
		const float dt = now - last;
		last = now;

		window->startFrame();
		
		if(m_debugMode)
		{
			m_debug.show();

			static bool wireframe = false;

			ImGui::Begin("Stats");
			ImGui::Checkbox("Wireframe", &wireframe);
			ImGui::Text("FPS: %i frame/s", fpsCurrent);
			ImGui::Text("Frame Time: %.2f ms/frame", static_cast<double>(dt));
			ImGui::Text("Vertices: %i", renderer.countTotalNumVertices());
			ImGui::SliderInt("Frame Time Sample Rate", &dtSampleRate, 1, 60);
			ImGui::Checkbox("Pause Frame Time", &pauseDt);

			if(t % dtSampleRate == 0 && !pauseDt)
			{
				ImGui::PlotVariable("Frame Time: ", dt);
			} else
			{
				ImGui::PlotVariable("Frame Time: ", FLT_MAX);
			}

			if(ImGui::Checkbox("VSync", &vsync))
			{
				window->setVSync(vsync);
			}

			if(ImGui::Checkbox("Fullscreen", &fullscreen))
			{
				window->setFullscreen(fullscreen);
			}

			ImGui::End();

			m_renderDevice->showShaderDebugUI();

			if(wireframe)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		m_camera->tick(dt);

		renderer.setViewMatrix(m_camera->calculateViewMatrix());

		showHintUi();

		renderer.render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		window->endFrame();
		t++;
	}

	renderer.destroy();
}

void Sandbox::onEvent(events::Event& event)
{
	auto test = events::EventDispatcher(event);
	test.dispatch<events::KeyPressedEvent>(std::bind(&Sandbox::onKeyPress, this, std::placeholders::_1));
	test.dispatch<events::WindowResizeEvent>(std::bind(&gfx::FPSCamera::onWindowResize, m_camera, std::placeholders::_1));
}

bool Sandbox::onKeyPress(events::KeyPressedEvent& event)
{
	if (event.getKeyCode() == events::Key::KEY_ESCAPE)
	{
		m_camera->enable(!m_camera->isEnabled());
	}
	else if (event.getKeyCode() == events::Key::KEY_K)
	{
		m_debugMode = !m_debugMode;
	}

	return true;
}

