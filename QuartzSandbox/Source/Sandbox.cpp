
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

void Sandbox::run()
{
	using namespace gfx::api;
	using namespace gfx::api::gl;

	gfx::IWindow* window = m_appData->window;

	IRenderDevice* renderDevice = new GLRenderDevice();
	renderDevice->create();
	
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,//  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,//  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f//,  0.0f, 0.0f, 1.0f   // top 
	};

	float colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	InputLayout layout = {
		{ VertexElementType::Vec3f, 0, 0, 0, false },
		{ VertexElementType::Vec3f, 1, 1, 0, false }
	};

	VertexBufferHandle vbo = renderDevice->createVertexBuffer();
	renderDevice->setBufferData(vbo, vertices, sizeof(vertices));

	VertexBufferHandle cbo = renderDevice->createVertexBuffer();
	renderDevice->setBufferData(cbo, colors, sizeof(colors));

	ShaderPipelineHandle shader = renderDevice->createShaderPipeline("assets/shaders/basic.shader", layout);

	renderDevice->setShaderPipeline(shader);
	while (window->isRunning())
	{
		window->startFrame();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		renderDevice->setVertexBufferStream(vbo, 0, 3 * sizeof(float), 0);
		renderDevice->setVertexBufferStream(cbo, 1, 3 * sizeof(float), 0);
		renderDevice->drawArrays(0, 3);

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

	return true;
}

