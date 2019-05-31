
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

#include <Quartz/Core/Graphics/API/IRenderDevice.hpp>
#include <Quartz/Core/Graphics/API/GL/GLRenderDevice.hpp>
#include <imgui/imgui.h>

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
	using namespace gfx::api;
	using namespace gfx::api::gl;

	gfx::IWindow* window = m_appData->window;
	window->registerEventListener([&](qz::events::Event& e) { onEvent(e); });

	m_renderDevice = new GLRenderDevice();
	m_renderDevice->create();
	
	float bottomTriangleVertices[] = {
		 0.5f, -0.5f, 0.0f, 1.f, 0.f,
		-0.5f, -0.5f, 0.0f, 0.f, 0.0f,
		 0.0f,  0.0f, 0.0f, 0.5f, 0.5f
	};

	float topTriangleVertices[] = {
		 0.5f, 0.5f, 0.0f, 0.f, 1.f,
		-0.5f, 0.5f, 0.0f, 1.f, 1.f,
		 0.0f, 0.0f, 0.0f, 0.5f, 0.5f
	};

	InputLayout layout = {
		{ VertexElementType::Vec3f, 0, 0, 0,                 false },
		{ VertexElementType::Vec2f, 0, 1, 3 * sizeof(float), false }
	};

	VertexBufferHandle bufferTriangleBuffer = m_renderDevice->createVertexBuffer();
	m_renderDevice->setBufferData(bufferTriangleBuffer, bottomTriangleVertices, sizeof(bottomTriangleVertices));

	VertexBufferHandle topTriangleBuffer = m_renderDevice->createVertexBuffer();
	m_renderDevice->setBufferData(topTriangleBuffer, topTriangleVertices, sizeof(topTriangleVertices));
	const std::string testShaderSource = 
	R"(#shader frag
#include "test.frag"
#shader vertex
#include "test.vert"
	)";
	//ShaderPipelineHandle shader = m_renderDevice->createShaderPipelineFromSource("assets/shaders/tests/", testShaderSource, layout);
	ShaderPipelineHandle shader = m_renderDevice->createShaderPipelineFromFile("assets/shaders/tests/test.shader", layout);
	UniformHandle colorHandle = m_renderDevice->createUniform(shader, "u_color", UniformType::COLOR3);
	UniformHandle samplerUniform = m_renderDevice->createUniform(shader, "u_sampler", UniformType::SAMPLER);
	int id = 0;
	m_renderDevice->setUniformValue(samplerUniform, &id, 1);

	int width = -1, height = -1, nbChannels = -1;
	unsigned char* image = stbi_load("assets/textures/dirt.png", &width, &height, &nbChannels, 0);
	TextureHandle texture = m_renderDevice->createTexture(image, width, height);

	float color[3] = { 1.0f, 1.0f, 1.0f };
	m_renderDevice->setUniformValue(colorHandle, color, 1);

	m_renderDevice->setShaderPipeline(shader);
	while (window->isRunning())
	{
		window->startFrame();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		showHintUi();
		showDebugUi();

		m_renderDevice->setTexture(texture, 0);

		m_renderDevice->setVertexBufferStream(bufferTriangleBuffer, 0, 5 * sizeof(float), 0);
		m_renderDevice->draw(0, 3);

		m_renderDevice->setVertexBufferStream(topTriangleBuffer, 0, 5 * sizeof(float), 0);
		m_renderDevice->draw(0, 3);

		window->endFrame();
	}
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

