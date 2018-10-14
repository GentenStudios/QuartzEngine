#pragma once

#include "engine/math/vector3.hpp"
#include "engine/math/matrix4x4.hpp"

#include <GLFW/glfw3.h>

namespace phoenix {
	/**
	 * @brief Provides a free roam/flying Camera controlled by W/S/A/S and mouse look.
	 * Takes control of mouse, to free the mouse toggle the `enabled` member variable.
	 */
	class FreeRoamCamera {
	public:
		/**
		 * @brief Contructs the camera, setting the window that input should be captured relative to.
		 * @param window The GLFWwindow that input should be captured from/relative to.
		 */
		FreeRoamCamera(GLFWwindow *window);

		/**
		 * @brief Updates this cameras state (rotation, position etc..). If `enabled` is false then this function does no work.
		 * @param dt Game loop delta time (in seconds) 
		 */
		void tick(float dt);

		/**
		 * @brief Calculates the view matrix for this camera.
		 * @return The view matrix of this camera.
		 */
		Matrix4x4 calculateViewMatrix();

		bool enabled; //< Controls whether this class controls the mouse cursor. `true` means the mouse is locked, `false` means the mouse is not locked.
	
	private:
		Vector3 m_rotation;
		Vector3 m_position;
		Vector3 m_up;
		Vector3 m_direction;

		GLFWwindow *m_window;
	};
}