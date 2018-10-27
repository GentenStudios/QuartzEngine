#pragma once

#include "engine/common.hpp"
#include "engine/graphics/Camera.hpp"

using namespace phx::gfx;
using namespace phx;

const float MOUSE_SENSITIVITY = 0.005f;
const float MOVE_SPEED = 2.f;
const float HALF_PI = MathUtils::PI / 2;

static Vector2 lastMousePos = { 0, 0 };

FPSCam::FPSCam(IWindow* window) : m_window(window), enabled(true)
{
	window->setCursorState(CursorState::DISABLED);
	m_position = { 0.0f, 0.0f, 0.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };
	m_direction = { 0.0f, 0.0f, 0.0f };
	m_dt = 0.16f;
}

void FPSCam::cameraMoveEvent(CamDir direction)
{
	if (!enabled)
		return;

	float velocity = MOVE_SPEED * m_dt;
	
	switch (direction)
	{
	case CamDir::FORWARD:
		m_position += m_direction * velocity;
		break;
	case CamDir::BACKWARD:
		m_position -= m_direction * velocity;
		break;
	case CamDir::LEFT:
		m_position -= m_right * velocity;
		break;
	case CamDir::RIGHT:
		m_position += m_right * velocity;
		break;
	}
}

void FPSCam::cameraLookEvent(float x, float y)
{
	m_rotation.x += MOUSE_SENSITIVITY * m_dt * (lastMousePos.x - x);
	m_rotation.y += MOUSE_SENSITIVITY * m_dt * (lastMousePos.y - y);
	
	m_rotation.y = MathUtils::clamp(m_rotation.y, -HALF_PI, HALF_PI);

	m_direction.x = std::cos(m_rotation.y) * std::sin(m_rotation.x);
	m_direction.y = std::sin(m_rotation.y);
	m_direction.z = std::cos(m_rotation.y) * std::cos(m_rotation.x);

	m_right = Vector3(
		std::sin(m_rotation.x - HALF_PI),
		0.f,
		std::cos(m_rotation.x - HALF_PI)
	);

	m_up = Vector3::cross(m_right, m_direction);

	lastMousePos = { x, y };
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