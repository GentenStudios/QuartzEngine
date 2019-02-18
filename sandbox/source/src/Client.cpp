#include <client/Client.hpp>
#include <quartz/core/utilities/Config.hpp>

#include <glad/glad.h>
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
		-0.5f, -0.5f, -3.f,
		0.5f, -0.5f, -3.f,
		0.0f,  0.5f, -3.f
	};

	auto state = IStateManager::generateStateManager();
	auto buffer = IBuffer::generateBuffer(BufferTarget::ARRAY_BUFFER, BufferUsage::STATIC);
	auto shader = IShaderPipeline::generateShaderPipeline();

	buffer->setData(9 * sizeof(float), vertices);

	state->attachBuffer(buffer);

	shader->addStage(ShaderType::VERTEX_SHADER, utils::FileIO::readAllFile("assets/shaders/main.vert"));
	shader->addStage(ShaderType::FRAGMENT_SHADER, utils::FileIO::readAllFile("assets/shaders/main.frag"));
	shader->build();

	BufferLayout layout;
	layout.registerAttribute("a_Pos", gfx::DataType::FLOAT, 3, 3 * sizeof(float), 0, false);

	state->attachBufferLayout(layout, shader);

	Matrix4x4 model = Matrix4x4();

	float last = static_cast<float>(SDL_GetTicks());
	while (window->isRunning())
	{
		window->pollEvents();

		float now = static_cast<float>(SDL_GetTicks());
		float dt = now - last;
		last = now;

		m_camera->tick(dt);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

		shader->use();
		shader->setMat4("u_projection", m_camera->getProjection());
		shader->setMat4("u_view", m_camera->calculateViewMatrix());
		shader->setMat4("u_model", model);

		state->render(0, 3);

		window->swapBuffers();
	}
}

bool onClose(events::WindowCloseEvent e)
{
	LDEBUG("WOW! WINDOW IS CLOSING DOWN.");
	return true;
}

bool Sandbox::onClose(events::WindowCloseEvent& e)
{
	LDEBUG("Sandbox is shutting down.");

	return true;
}

void Sandbox::onEvent(events::Event& e)
{
	//auto test = events::EventDispatcher(e);
	//test.dispatch<events::WindowCloseEvent>(std::bind(&Sandbox::onClose, this, std::placeholders::_1));
	//test.dispatch<events::KeyPressedEvent>(std::bind(&gfx::FPSCamera::onKeyPress, m_camera, std::placeholders::_1));
	//test.dispatch<events::MouseMovedEvent>(std::bind(&gfx::FPSCamera::onMouseMove, m_camera, std::placeholders::_1));
	//test.dispatch<events::WindowResizeEvent>(std::bind(&gfx::FPSCamera::onWindowResize, m_camera, std::placeholders::_1));
}

bool onClose2(events::WindowCloseEvent e)
{
	LDEBUG("WOW! THE SECOND EVENT HANDLER IS WORKING!");
	return true;
}
