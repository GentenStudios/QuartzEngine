#include <client/Client.hpp>
#include <quartz/core/utilities/Config.hpp>

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <chrono>

using namespace client;
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
	gfx::IWindow* window = m_appData->window;

	m_camera = new gfx::FPSCamera(window);

	window->registerEventListener(std::bind(&Sandbox::onEvent, this, std::placeholders::_1));

	using namespace gfx::api;

	float vertices[] = {
		-1.f, -1.f, -3.f,
		1.f, -1.f, -3.f,
		0.0f,  1.f, -3.f
	};

	auto state = IStateManager::generateStateManager();
	auto buffer = IBuffer::generateBuffer(BufferTarget::ARRAY_BUFFER, BufferUsage::STATIC);
	auto shader = IShaderPipeline::generateShaderPipeline();

	buffer->setData(sizeof(vertices), vertices);

	state->attachBuffer(buffer);

	shader->addStage(ShaderType::VERTEX_SHADER, utils::FileIO::readAllFile("assets/shaders/main.vert"));
	shader->addStage(ShaderType::FRAGMENT_SHADER, utils::FileIO::readAllFile("assets/shaders/main.frag"));
	shader->build();

	BufferLayout layout;
	layout.registerAttribute("a_Pos", gfx::DataType::FLOAT, 3, 3 * sizeof(float), 0, false);

	state->attachBufferLayout(layout, shader);

	const Matrix4x4 model;

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

		m_camera->tick(dt);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		shader->use();
		shader->setMat4("u_projection", m_camera->getProjection());
		shader->setMat4("u_view", m_camera->calculateViewMatrix());
		shader->setMat4("u_model", model);

		state->render(0, 3);

		window->startGUIFrame();
		ImGui::Begin("Debug Information");
		ImGui::Text("FPS: %d", fpsCurrent);
		ImGui::Text("Frame Time: %f ms", dt);
		ImGui::End();
		window->endGUIFrame();

		window->swapBuffers();
		window->pollEvents();
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
