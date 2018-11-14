#pragma once

#include "engine/common.hpp"
#include "engine/graphics/Camera.hpp"

#include <SDL.h>

using namespace phx::gfx;
using namespace phx;

const float HALF_PI = MathUtils::PI / 2;

static Vector2 lastMousePos = { 0, 0 };

FPSCam::FPSCam(IWindow* window) : m_window(window), enabled(true)
{
	window->setCursorState(CursorState::DISABLED);
	m_controls.load();
}

void FPSCam::update(float dt)
{
	if (!enabled)
		return;

	const TVector2<int> mousePos = m_window->getMousePosition();
	
	int windowW, windowH;
	m_window->getSize(windowW, windowH);

	m_window->setMousePosition({ windowW / 2, windowH / 2 });

	const float sensitivity = m_controls.mouseSensitivity();

	m_rotation.x += sensitivity * dt * (windowW / 2.f - mousePos.x);
	m_rotation.y += sensitivity * dt * (windowH / 2.f - mousePos.y);
	
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

	if (m_window->isKeyDown(SDL_SCANCODE_Q)) {
		m_position.y -= moveSpeed * dt;
	}
	else if (m_window->isKeyDown(SDL_SCANCODE_E)) {
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

void CameraControls::load()
{
	m_controlsConfig = PHX_GET_CONFIG("Controls");
}

/*
 * Camera controls configuration & Defaults.
 */

const std::string CAMERA_KEYBOARD_SECTION = "CameraKeyboard";
const std::string CAMERA_MISC_SECTION = "CameraMisc";

SDL_Scancode CameraControls::moveForward()
{
	return m_controlsConfig->getScancode(CAMERA_KEYBOARD_SECTION, "moveForward", SDL_SCANCODE_W);
}

SDL_Scancode CameraControls::moveBackwards()
{
	return m_controlsConfig->getScancode(CAMERA_KEYBOARD_SECTION, "moveBackwards", SDL_SCANCODE_S);
}

SDL_Scancode CameraControls::strafeLeft()
{
	return m_controlsConfig->getScancode(CAMERA_KEYBOARD_SECTION, "strafeLeft", SDL_SCANCODE_A);
}

SDL_Scancode CameraControls::strafeRight()
{
	return m_controlsConfig->getScancode(CAMERA_KEYBOARD_SECTION, "strafeRight", SDL_SCANCODE_D);
}

float CameraControls::mouseSensitivity()
{
	return m_controlsConfig->getFloat(CAMERA_MISC_SECTION, "mouseSensitivty", 0.00005f);
}

float CameraControls::moveSpeed()
{
	return m_controlsConfig->getFloat(CAMERA_MISC_SECTION, "moveSpeed", 0.1f);
}
