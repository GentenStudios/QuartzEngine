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

bool FPSCamera::onKeyPress(const events::KeyPressedEvent& key)
{
	const events::Key keycode = key.getKeyCode();

	if (keycode == events::Key::KEY_W)
	{
		m_position += m_direction * m_dt * MOVE_SPEED;
	}
	else if (keycode == events::Key::KEY_S) {
		m_position -= m_direction * m_dt * MOVE_SPEED;
	}

	if (keycode == events::Key::KEY_A) {
		m_position -= m_right * m_dt * MOVE_SPEED;
	}
	else if (keycode == events::Key::KEY_D) {
		m_position += m_right * m_dt * MOVE_SPEED;
	}

	if (keycode == events::Key::KEY_LSHIFT) {
		m_position.y -= MOVE_SPEED * m_dt;
	}
	else if (keycode == events::Key::KEY_SPACE) {
		m_position.y += MOVE_SPEED * m_dt;
	}

	return true;
}

bool FPSCamera::onMouseMove(const events::MouseMovedEvent& mouse)
{
	const Vector2 mousePos = mouse.getPos();

	m_window->setCursorPosition(m_windowCentre);

	m_rotation.x += SENSITIVITY * m_dt * (m_windowCentre.x - mousePos.x);
	m_rotation.y += SENSITIVITY * m_dt * (m_windowCentre.y - mousePos.y);

	m_rotation.y = math::clamp(m_rotation.y, -HALF_PI, HALF_PI);

	m_direction.x = std::cos(m_rotation.y) * std::sin(m_rotation.x);
	m_direction.y = std::sin(m_rotation.y);
	m_direction.z = std::cos(m_rotation.y) * std::cos(m_rotation.x);

	m_right = {
		std::sin(m_rotation.x - HALF_PI),
		0.f,
		std::cos(m_rotation.x - HALF_PI)
	};

	m_up = Vector3::cross(m_right, m_direction);

	return true;
}

bool FPSCamera::onWindowResize(const events::WindowResizeEvent& window)
{
	m_projection = Matrix4x4::perspective(static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight()), 45.f, 1000.f, 0.1f);

	m_windowCentre = { window.getWidth() / 2.f, window.getHeight() / 2.f };

	return true;
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
	m_dt = dt;
}
