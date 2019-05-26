
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

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
	static int corner = 1;
	static bool p_open = true;

	ImGuiIO& io = ImGui::GetIO();
	if (corner != -1)
	{
		ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
	if (ImGui::Begin("Example: Simple overlay", &p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::Text("Press K to toggle developer mode!");
	}
	ImGui::End();
}

void Sandbox::showDebugUi()
{
	static bool shaderDebugUi = true, imguiDemo = false;
	if (m_debugMode)
	{

		ImGui::BeginMainMenuBar();
		if (ImGui::MenuItem("Shader Debug UI"))
		{
			shaderDebugUi = !shaderDebugUi;
		}
		if (ImGui::MenuItem("ImGui Demo"))
		{
			imguiDemo = !imguiDemo;
		}

		ImGui::EndMainMenuBar();

		if (imguiDemo)
		{
			ImGui::ShowDemoWindow();
		}

		if (shaderDebugUi)
		{
			m_renderDevice->showShaderDebugUI();
		}
	}
}

void Sandbox::run()
{
	using namespace gfx::rhi;
	using namespace gfx::rhi::gl;

	gfx::IWindow* window = m_appData->window;
	window->registerEventListener([&](qz::events::Event& e) { onEvent(e); });

	voxels::BlockRegistery* blocksRegistery = voxels::BlockRegistery::get();
	voxels::BlockType* air = blocksRegistery->registerBlock({"Air", "core:air", voxels::BlockTypeCategory::AIR});
	voxels::BlockType* dirt = blocksRegistery->registerBlock({"Dirt", "core:dirt", voxels::BlockTypeCategory::SOLID});


	m_renderDevice = new GLRenderDevice();
	m_renderDevice->create();

	gfx::Mesh mesh(3);
	mesh.addVertex({{1.f, 1.f, 1.0f}, {0.f, 1.f}});
	mesh.addVertex({{-1.f, 1.f, 1.0f}, {1.f, 1.f}});
	mesh.addVertex({{0.0f, 0.0f, 1.0f}, {0.5f, 0.5f}});

	gfx::ForwardMeshRenderer renderer(m_renderDevice);
	renderer.submitMesh(&mesh);

	InputLayout layout = {
		{ VertexElementType::Vec3f, 0, 0, 0,                 false },
		{ VertexElementType::Vec2f, 0, 1, 3 * sizeof(float), false }
	};

	ShaderPipelineHandle shader = m_renderDevice->createShaderPipeline("assets/shaders/basic.shader", layout);

	m_renderDevice->setShaderPipeline(shader);

	m_camera = new gfx::FPSCamera(window);
	m_camera->setProjection(Matrix4x4::perspective(1280.f / 720.f, 90.f, 100.f, 0.1f));

	auto viewUniform = m_renderDevice->createUniform(shader, "u_view", UniformType::MAT4);
	auto projectionUniform = m_renderDevice->createUniform(shader, "u_projection", UniformType::MAT4);

	Matrix4x4 projection = m_camera->getProjection();
	m_renderDevice->setUniformValue(projectionUniform, &projection, 1);

	std::size_t fpsLastTime = SDL_GetTicks();
	int fpsCurrent = 0; // the current FPS.
	int fpsFrames = 0; // frames passed since the last recorded fps.

	float last = static_cast<float>(SDL_GetTicks());
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
			ImGui::Begin("Stats");
			ImGui::Text("FPS: %i", fpsCurrent);
			ImGui::Text("Delta: %f", dt);
			ImGui::Text("Vertices: %i", renderer.countTotalNumVertices());
			ImGui::End();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		m_camera->tick(dt);

		Matrix4x4 view = m_camera->calculateViewMatrix();
		m_renderDevice->setUniformValue(viewUniform, &view, 1);

		showHintUi();
		showDebugUi();

		renderer.render();

		window->endFrame();
	}

	m_renderDevice->freeShaderPipeline(shader);
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

