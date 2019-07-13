// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#include <Quartz/QuartzPCH.hpp>
#include <Quartz/Graphics/Camera.hpp>

#include <cmath>

const float HALF_PI = qz::math::PI / 2;
const float MOVE_SPEED = 0.01f;
const float SENSITIVITY = 0.00005f;

using namespace qz::gfx;
using namespace qz;

FPSCamera::FPSCamera(IWindow* window) : m_window(window)
{
	window->setCursorState(CursorState::DISABLED);

	const Vector2 windowSize = window->getSize();
	m_projection = Matrix4x4::perspective(windowSize.x / windowSize.y, 45.f, 1000.f, 0.1f);

	m_windowCentre = { std::floor(windowSize.x / 2.f), std::floor(windowSize.y / 2.f) };
}

qz::Vector3 FPSCamera::getPosition() const
{
	return m_position;
}

qz::Vector3 FPSCamera::getDirection() const
{
	return m_direction;
}

void FPSCamera::resizeProjection(events::Event e)
{
	m_projection = Matrix4x4::perspective(static_cast<float>(e.size.width) / static_cast<float>(e.size.height), 45.f, 1000.f, 0.1f);
	m_windowCentre = { static_cast<float>(static_cast<int>(e.size.width / 2)), static_cast<float>(static_cast<int>(e.size.height / 2)) };
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

void FPSCamera::enable(bool enabled)
{
	if (enabled)
		m_window->setCursorState(gfx::CursorState::DISABLED);
	else
		m_window->setCursorState(gfx::CursorState::NORMAL);

	m_enabled = enabled;
}

void FPSCamera::tick(float dt)
{
	if (!m_enabled)
		return;

	const Vector2 mousePos = m_window->getCursorPosition();

	m_window->setCursorPosition(m_windowCentre);

	const float sensitivity = SENSITIVITY;

	m_rotation.x += sensitivity * dt * (m_windowCentre.x - mousePos.x);
	m_rotation.y += sensitivity * dt * (m_windowCentre.y - mousePos.y);

	m_rotation.y = math::clamp(m_rotation.y, -HALF_PI, HALF_PI);

	m_direction.x = std::cos(m_rotation.y) * std::sin(m_rotation.x);
	m_direction.y = std::sin(m_rotation.y);
	m_direction.z = std::cos(m_rotation.y) * std::cos(m_rotation.x);

	const Vector3 right = {
		std::sin(m_rotation.x - HALF_PI),
		0.f,
		std::cos(m_rotation.x - HALF_PI)
	};

	m_up = Vector3::cross(right, m_direction);

	const float moveSpeed = MOVE_SPEED;

	if (m_window->isKeyDown(events::Keys::KEY_W))
	{
		m_position += m_direction * dt * moveSpeed;
	}
	else if (m_window->isKeyDown(events::Keys::KEY_S))
	{
		m_position -= m_direction * dt * moveSpeed;
	}

	if (m_window->isKeyDown(events::Keys::KEY_A))
{
		m_position -= right * dt * moveSpeed;
	}
	else if (m_window->isKeyDown(events::Keys::KEY_D))
	{
		m_position += right * dt * moveSpeed;
	}

	if (m_window->isKeyDown(events::Keys::KEY_SPACE))
	{
		m_position.y += dt * moveSpeed;
	}
	else if (m_window->isKeyDown(events::Keys::KEY_LEFT_SHIFT))
	{
		m_position.y -= dt * moveSpeed;
	}
}

