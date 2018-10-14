#include "engine/camera.hpp"
#include "engine/math/mathutils.hpp"

#include <cmath>

using namespace phoenix;

const float MOUSE_SENSITIVITY = 0.000075f;
const float MOVE_SPEED = 0.01f;

FreeRoamCamera::FreeRoamCamera(GLFWwindow* window)
	: m_window(window), enabled(true)
{
	int w, h;
	glfwGetWindowSize(window, &w, &h);
	glfwSetCursorPos(window, w / 2, h / 2);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void FreeRoamCamera::tick(float dt)
{
	if (!enabled)
		return;

	double mx, my;
	glfwGetCursorPos(m_window, &mx, &my);

	int w, h;
	glfwGetWindowSize(m_window, &w, &h);

	glfwSetCursorPos(m_window, w / 2, h / 2);

	m_rotation.x += MOUSE_SENSITIVITY * dt * static_cast<float>(w / 2.0 - mx);
	m_rotation.y += MOUSE_SENSITIVITY * dt * static_cast<float>(h / 2.0 - my);

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

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_position += m_direction * dt * MOVE_SPEED;

	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_position -= m_direction * dt * MOVE_SPEED;

	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_position += right * dt * MOVE_SPEED;

	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_position -= right * dt * MOVE_SPEED;

}

Matrix4x4 FreeRoamCamera::calculateViewMatrix()
{
	Matrix4x4 mat4;
	return mat4;
}