#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/Camera.hpp>

const float HALF_PI = qz::math::PI / 2;
const float MOVE_SPEED = 0.1f;
const float SENSITIVITY = 0.00005f;

using namespace qz::gfx;
using namespace qz;

FPSCamera::FPSCamera(IWindow* window) : m_window(window)
{
	//window->setCursorState(CursorState::DISABLED);

	const Vector2 windowSize = window->getSize();
	m_projection = Matrix4x4::perspective(static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y), 45.f, 1000.f, 0.1f);

	m_windowCentre = { static_cast<float>(static_cast<int>(windowSize.x / 2)), static_cast<float>(static_cast<int>(windowSize.y / 2)) };
}

qz::Vector3 FPSCamera::getPosition() const
{
	return m_position;
}

qz::Vector3 FPSCamera::getDirection() const
{
	return m_direction;
}

void FPSCamera::setProjection(const Matrix4x4& projection)
{
	m_projection = projection;
}

qz::Matrix4x4 FPSCamera::getProjection() const
{
	return m_projection;
}

qz::Matrix4x4 FPSCamera::calculateViewMatrix() const
{
	const Vector3 centre = m_position + m_direction;

	return Matrix4x4::lookAt(m_position, centre, m_up);
}

void FPSCamera::tick(float dt)
{
	const Vector2 mousePos = m_window->getCursorPosition();

	m_window->setCursorPosition(m_windowCentre);

	const float sensitivity = SENSITIVITY;

	m_rotation.x += sensitivity * dt * (m_windowCentre.x - mousePos.x);
	m_rotation.y += sensitivity * dt * (m_windowCentre.y - mousePos.y);

	m_rotation.y = math::clamp(m_rotation.y, -HALF_PI, HALF_PI);

	m_direction.x = std::cos(m_rotation.y) * std::sin(m_rotation.x);
	m_direction.y = std::sin(m_rotation.y);
	m_direction.z = std::cos(m_rotation.y) * std::cos(m_rotation.x);

	const Vector3 right(
		std::sin(m_rotation.x - HALF_PI),
		0.f,
		std::cos(m_rotation.x - HALF_PI)
	);

	m_up = Vector3::cross(right, m_direction);

	const float moveSpeed = MOVE_SPEED;

	if (m_window->isKeyDown(events::Key::KEY_W)) {
		m_position += m_direction * dt * moveSpeed;
	}
	else if (m_window->isKeyDown(events::Key::KEY_S)) {
		m_position -= m_direction * dt * moveSpeed;
	}

	if (m_window->isKeyDown(events::Key::KEY_A)) {
		m_position -= right * dt * moveSpeed;
	}
	else if (m_window->isKeyDown(events::Key::KEY_D)) {
		m_position += right * dt * moveSpeed;
	}

	if (m_window->isKeyDown(events::Key::KEY_A)) {
		m_position.y -= moveSpeed * dt;
	}
	else if (m_window->isKeyDown(events::Key::KEY_A)) {
		m_position.y += moveSpeed * dt;
	}
}
