#include <engine/core/graphics/Camera.hpp>
#include <GL/glew.h>

using namespace phx::gfx;
using namespace phx;

const float HALF_PI = MathUtils::PI / 2;

static Vector2 lastMousePos = { 0, 0 };

FPSCam::FPSCam(IWindow* window) : m_window(window), enabled(true)
{
	window->setCursorState(CursorState::DISABLED);
	m_controls.load();

	int w = 0, h = 0;
	window->getSize(w, h);
	m_projection = Matrix4x4::perspective(static_cast<float>(w) / static_cast<float>(h), 45.f, 1000.f, 0.1f);
	
	m_windowCentre = { w / 2, h / 2 };

	window->addWindowEventCallback(events::WindowEventType::RESIZED, [this]() {
		int w = 0, h = 0;
		this->m_window->getSize(w, h);
	
		this->setProjection(Matrix4x4::perspective(static_cast<float>(w) / static_cast<float>(h), 45.f, 1000.f, 0.1f));
		this->m_windowCentre = { w / 2, h / 2 };
	});
}

void FPSCam::update(float dt)
{
	if (!enabled)
		return;

	const TVector2<int> mousePos = m_window->getMousePosition();
	
	m_window->setMousePosition(m_windowCentre);

	const float sensitivity = m_controls.mouseSensitivity();

	m_rotation.x += sensitivity * dt * (m_windowCentre.x - mousePos.x);
	m_rotation.y += sensitivity * dt * (m_windowCentre.y - mousePos.y);
	
	m_rotation.y = MathUtils::clamp(m_rotation.y, -HALF_PI, HALF_PI);

	m_direction.x = std::cos(m_rotation.y) * std::sin(m_rotation.x);
	m_direction.y = std::sin(m_rotation.y);
	m_direction.z = std::cos(m_rotation.y) * std::cos(m_rotation.x);

	const Vector3 right(
		std::sin(m_rotation.x - HALF_PI),
		0.f,
		std::cos(m_rotation.x - HALF_PI)
	);

	m_up = Vector3::cross(right, m_direction);

	const float moveSpeed = m_controls.moveSpeed();

	if (m_window->isKeyDown(m_controls.moveForward())) {
		m_position += m_direction * dt * moveSpeed;
	}
	else if (m_window->isKeyDown(m_controls.moveBackwards())) {
		m_position -= m_direction * dt * moveSpeed;
	}

	if (m_window->isKeyDown(m_controls.strafeLeft())) {
		m_position -= right * dt * moveSpeed;
	}
	else if (m_window->isKeyDown(m_controls.strafeRight())) {
		m_position += right * dt * moveSpeed;
	}

	if (m_window->isKeyDown(events::Keys::KEY_Q)) {
		m_position.y -= moveSpeed * dt;
	}
	else if (m_window->isKeyDown(events::Keys::KEY_E)) {
		m_position.y += moveSpeed * dt;
	}
}

Matrix4x4 FPSCam::calculateViewMatrix()
{
	Vector3 centre = m_position + m_direction;

	return Matrix4x4::lookAt(m_position, centre, m_up);
}

Vector3 FPSCam::getPosition()
{
	return m_position;
}

Vector3 FPSCam::getDirection()
{
	return m_direction;
}

Matrix4x4 FPSCam::getProjection()
{
	return m_projection;
}

void phx::gfx::FPSCam::setProjection(const Matrix4x4 & projection)
{
	m_projection = projection;
}

void CameraControls::load()
{
	m_controlsConfig = PHX_GET_CONFIG("Controls");
}

/*
 * Camera controls configuration & Defaults.
 */

const std::string CAMERA_KEYBOARD_SECTION = "CameraKeyboard";
const std::string CAMERA_MISC_SECTION = "CameraMisc";

events::Keys CameraControls::moveForward()
{
	return m_controlsConfig->getScancode(CAMERA_KEYBOARD_SECTION, "moveForward", events::Keys::KEY_W);
}

events::Keys CameraControls::moveBackwards()
{
	return m_controlsConfig->getScancode(CAMERA_KEYBOARD_SECTION, "moveBackwards", events::Keys::KEY_S);
}

events::Keys CameraControls::strafeLeft()
{
	return m_controlsConfig->getScancode(CAMERA_KEYBOARD_SECTION, "strafeLeft", events::Keys::KEY_A);
}

events::Keys CameraControls::strafeRight()
{
	return m_controlsConfig->getScancode(CAMERA_KEYBOARD_SECTION, "strafeRight", events::Keys::KEY_D);
}

float CameraControls::mouseSensitivity()
{
	return m_controlsConfig->getFloat(CAMERA_MISC_SECTION, "mouseSensitivty", 0.00005f);
}

float CameraControls::moveSpeed()
{
	return m_controlsConfig->getFloat(CAMERA_MISC_SECTION, "moveSpeed", 0.1f);
}
