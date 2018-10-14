#pragma once

#include "engine/math/vector3.hpp"
#include "engine/math/matrix4x4.hpp"

#include <GLFW/glfw3.h>

namespace phoenix {
	class FreeRoamCamera {
	public:
		FreeRoamCamera(GLFWwindow *window);

		void tick(float dt);

		Matrix4x4 calculateViewMatrix();

		bool enabled;
	private:
		Vector3 m_rotation;
		Vector3 m_position;
		Vector3 m_up;
		Vector3 m_direction;

		GLFWwindow *m_window;
	};
}