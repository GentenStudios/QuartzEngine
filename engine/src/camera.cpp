#include "engine/camera.hpp"
#include "engine/math/mathutils.hpp"

#include <cmath>

using namespace phoenix;
using namespace phoenix::graphics;

const float MOUSE_SENSITIVITY = 0.005f;
const float MOVE_SPEED = 2.f;

FreeRoamCamera::FreeRoamCamera(phoenix::graphics::Window* window)
	: m_window(window), enabled(true)
{
	window->setCursorState(phoenix::graphics::CursorState::DISABLED);
}

static XyData _lastMousePos = { 0, 0 };

void FreeRoamCamera::tick(float dt)
{
	if (!enabled)
		return;

	auto mousePos = m_window->getCursorPos();
	auto windowSize = m_window->getWindowSize();

	m_rotation.x += MOUSE_SENSITIVITY * dt * static_cast<float>(_lastMousePos.x - mousePos.x);
	m_rotation.y += MOUSE_SENSITIVITY * dt * static_cast<float>(_lastMousePos.y - mousePos.y);

	const float HALF_PI = MathUtils::PI / 2.f;

	m_rotation.y = MathUtils::clamp(m_rotation.y, -HALF_PI, HALF_PI);

	m_direction.x = std::cos(m_rotation.y) * std::sin(m_rotation.x);
	m_direction.y = std::sin(m_rotation.y);
	m_direction.z = std::cos(m_rotation.y) * std::cos(m_rotation.x);

	Vector3 right(
		std::sin(m_rotation.x - HALF_PI),
		0.f,
		std::cos(m_rotation.x - HALF_PI)
	);

	m_up = Vector3::cross(right, m_direction);

	if (m_window->getKeyState(GLFW_KEY_W) == GLFW_PRESS)
		m_position += m_direction * dt * MOVE_SPEED;

	if (m_window->getKeyState(GLFW_KEY_S) == GLFW_PRESS)
		m_position -= m_direction * dt * MOVE_SPEED;

	if (m_window->getKeyState(GLFW_KEY_D) == GLFW_PRESS)
		m_position += right * dt * MOVE_SPEED;

	if (m_window->getKeyState(GLFW_KEY_A) == GLFW_PRESS)
		m_position -= right * dt * MOVE_SPEED;

	_lastMousePos = mousePos;
}

Matrix4x4 FreeRoamCamera::calculateViewMatrix()
{
	Vector3 centre = m_position + m_direction;

	return Matrix4x4::lookAt(m_position, centre, m_up);
}

Vector3 FreeRoamCamera::getPosition()
{
	return m_position;
}
