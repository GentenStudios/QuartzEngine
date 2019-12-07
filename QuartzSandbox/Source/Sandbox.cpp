
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <Quartz.hpp>
#include <Sandbox/Sandbox.hpp>

#include <LLGL/LLGL.h>

#include <iostream>

using namespace sandbox;
using namespace qz;

struct Vertex
{
	math::vec2       position;
	LLGL::ColorRGBAub color;
};

Sandbox::Sandbox()
{
	utils::Logger::instance()->initialise("Sandbox.log",
	                                      utils::LogVerbosity::DEBUG);
}

Sandbox::~Sandbox() {}

void Sandbox::run()
{
	std::cout << "Yo waddup" << std::endl;
	LINFO("YO WADDUP!");

	std::unique_ptr<LLGL::RenderSystem> renderer =
	    LLGL::RenderSystem::Load("OpenGL");

	LLGL::RenderContextDescriptor contextDesc;
	{
		contextDesc.videoMode.resolution = {800, 600};
		contextDesc.vsync.enabled        = true;
		contextDesc.samples              = 8;
	}
	LLGL::RenderContext* context = renderer->CreateRenderContext(contextDesc);

	const auto& info = renderer->GetRendererInfo();

	std::cout << "Renderer:         " << info.rendererName << std::endl;
	std::cout << "Device:           " << info.deviceName << std::endl;
	std::cout << "Vendor:           " << info.vendorName << std::endl;
	std::cout << "Shading Language: " << info.shadingLanguageName << std::endl;

	auto& window = LLGL::CastTo<LLGL::Window>(context->GetSurface());
	window.SetTitle(L"heehaw hilarious");
	window.Show();

	float  s          = 0.5;
	Vertex vertices[] = {
	    {{0, s}, {255, 0, 0, 255}},   // 1st vertex: center-top, red
	    {{s, -s}, {0, 255, 0, 255}},  // 2nd vertex: right-bottom, green
	    {{-s, -s}, {0, 0, 255, 255}}, // 3rd vertex: left-bottom, blue
	};

	// Vertex format
	LLGL::VertexFormat vertexFormat;

	// Append 2D float vector for position attribute
	vertexFormat.AppendAttribute({"position", LLGL::Format::RG32Float});

	// Append 3D unsigned byte vector for color
	vertexFormat.AppendAttribute({"color", LLGL::Format::RGBA8UNorm});

	// Update stride in case out vertex structure is not 4-byte aligned
	vertexFormat.SetStride(sizeof(Vertex));

	// Create vertex buffer
	LLGL::BufferDescriptor vertexBufferDesc;
	{
		vertexBufferDesc.size =
		    sizeof(vertices); // Size (in bytes) of the vertex buffer
		vertexBufferDesc.bindFlags =
		    LLGL::BindFlags::VertexBuffer; // Enables the buffer to be bound to
		                                   // a vertex buffer slot
		vertexBufferDesc.vertexAttribs =
		    vertexFormat.attributes; // Vertex format layout
	}
	LLGL::Buffer* vertexBuffer =
	    renderer->CreateBuffer(vertexBufferDesc, vertices);

	const auto& languages = renderer->GetRenderingCaps().shadingLanguages;

	LLGL::ShaderDescriptor vertShaderDesc, fragShaderDesc;

	// Create shaders
	LLGL::Shader* vertShader = nullptr;
	LLGL::Shader* fragShader = nullptr;

	if (std::find(languages.begin(), languages.end(),
	              LLGL::ShadingLanguage::GLSL) != languages.end())
	{
		vertShaderDesc = {LLGL::ShaderType::Vertex, "assets/shaders/Example.vert"};
		fragShaderDesc = {LLGL::ShaderType::Fragment, "assets/shaders/Example.frag"};
	}
	// Specify vertex attributes for vertex shader
	vertShaderDesc.vertex.inputAttribs = vertexFormat.attributes;

	vertShader = renderer->CreateShader(vertShaderDesc);
	fragShader = renderer->CreateShader(fragShaderDesc);

	// Create shader program which is used as composite
	LLGL::ShaderProgramDescriptor shaderProgramDesc;
	{
		shaderProgramDesc.vertexShader   = vertShader;
		shaderProgramDesc.fragmentShader = fragShader;
	}
	LLGL::ShaderProgram* shaderProgram = renderer->CreateShaderProgram(shaderProgramDesc);

    // Link shader program and check for errors
	if (shaderProgram->HasErrors())
		throw std::runtime_error(shaderProgram->GetReport());

	LLGL::GraphicsPipelineDescriptor pipelineDesc;
	{
		pipelineDesc.shaderProgram = shaderProgram;
		pipelineDesc.renderPass    = context->GetRenderPass();
		pipelineDesc.rasterizer.multiSampleEnabled = (contextDesc.samples > 1);
	}

	// Create graphics pipeline
	LLGL::PipelineState*        pipeline = nullptr;
	pipeline = renderer->CreatePipelineState(pipelineDesc);

	// Get command queue to record and submit command buffers
	LLGL::CommandQueue* queue = renderer->GetCommandQueue();

	// Create command buffer to submit subsequent graphics commands to the GPU
	LLGL::CommandBuffer* commands = renderer->CreateCommandBuffer();

	// Enter main loop
	while (window.ProcessEvents())
	{
		// Begin recording commands
		commands->Begin();
		{
			// Set viewport and scissor rectangle
			commands->SetViewport(context->GetResolution());

			// Set graphics pipeline
			commands->SetPipelineState(*pipeline);

			// Set vertex buffer
			commands->SetVertexBuffer(*vertexBuffer);

			// Set the render context as the initial render target
			commands->BeginRenderPass(*context);
			{
				// Clear color buffer
				commands->Clear(LLGL::ClearFlags::Color);

				// Draw triangle with 3 vertices
				commands->Draw(3, 0);
			}
			commands->EndRenderPass();
		}
		commands->End();
		queue->Submit(*commands);

		// Present the result on the screen
		context->Present();
	}
}

#undef main
int main(int argc, char** argv)
{
	Sandbox sandbox;
	sandbox.run();

	return 0;
}
