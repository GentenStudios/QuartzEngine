#pragma once

#include <engine/core/graphics/Camera.hpp>

using namespace phx::gfx;
using namespace phx;

const float MOUSE_SENSITIVITY = 0.00005f;
const float MOVE_SPEED = 0.1f;
const float HALF_PI = MathUtils::PI / 2;

static Vector2 lastMousePos = { 0, 0 };

FPSCam::FPSCam(IWindow* window) : m_window(window), enabled(true)
{
	window->setCursorState(CursorState::DISABLED);
}

void FPSCam::update(float dt)
{
	if (!enabled)
		return;

	TVector2<int> mousePos = m_window->getMousePosition();
	
	int windowW, windowH;
	m_window->getSize(windowW, windowH);

	m_window->setMousePosition({ windowW / 2, windowH / 2 });

	m_rotation.x += MOUSE_SENSITIVITY * dt * (windowW / 2.f - mousePos.x);
	m_rotation.y += MOUSE_SENSITIVITY * dt * (windowH / 2.f - mousePos.y);
	
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

	if (m_window->isKeyDown(SDL_SCANCODE_W)) {
		m_position += m_direction * dt * MOVE_SPEED;
	}
	else if (m_window->isKeyDown(SDL_SCANCODE_S)) {
		m_position -= m_direction * dt * MOVE_SPEED;
	}

	if (m_window->isKeyDown(SDL_SCANCODE_A)) {
		m_position -= right * dt * MOVE_SPEED;
	}
	else if (m_window->isKeyDown(SDL_SCANCODE_D)) {
		m_position += right * dt * MOVE_SPEED;
	}

	if (m_window->isKeyDown(SDL_SCANCODE_Q)) {
		m_position.y -= MOVE_SPEED * dt;
	}
	else if (m_window->isKeyDown(SDL_SCANCODE_E)) {
		m_position.y += MOVE_SPEED * dt;
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