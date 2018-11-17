/**
 * @file Camera.hpp
 * @brief File for the Camera Class/Function definitions
 */

#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/math/Vector2.hpp>
#include <engine/core/math/Vector3.hpp>
#include <engine/core/math/Matrix4x4.hpp>
#include <engine/core/math/MathUtils.hpp>

#include <engine/core/graphics/IWindow.hpp>
#include <SDL.h>

#include <engine/core/utils/Config.hpp>
#include "engine/core/events/Keys.hpp"

namespace phx
{
	namespace gfx
	{
		/**
		 * @brief Class that gets Camera Controls from using the Configuration reader.
		 */
		class CameraControls
		{
		public:
			/**
			 * @brief Get configuration from Camera Controls INI file. 
			 */
			void load();

			/**
			 * @brief Get the key assigned to moving forward.
			 * 
			 * @return An events::Keys ENUM value to use straight away in the camera classes.
			 */
			events::Keys moveForward();

			/**
			 * @brief Get the key assigned to moving backwards.
			 * 
			 * @return An events::Keys ENUM value to use straight away in the camera classes.
			 */
			events::Keys moveBackwards();

			/**
			 * @brief Get the key assigned to strafing left.
			 * 
			 * @return An events::Keys ENUM value to use straight away in the camera classes.
			 */
			events::Keys strafeLeft();

			/**
			 * @brief Get the key assigned to strafing right.
			 * 
			 * @return An events::Keys ENUM value to use straight away in the camera classes.
			 */
			events::Keys strafeRight();

			/**
			 * @brief Get the mouse sensitivity from the Config file.
			 * 
			 * @return The mouse sensitivity, as a float, ready to use wherever necessary.
			 */
			float mouseSensitivity();

			/**
			 * @brief Get the move speed from the Config file.
			 * 
			 * @return The move speed, as a float, ready to use wherever necessary.
			 */
			float moveSpeed();

		private:
			/// @brief ConfigFile Object to store the values that are retreived.
			ConfigFile* m_controlsConfig;
		};

		class FPSCam
		{
		public:
			/**
			 * @brief Construct a new FPSCam object
			 * 
			 * @param A window object, mainly used to check for key presses.
			 */
			FPSCam(IWindow* window);
			~FPSCam() {};

			/**
			 * @brief Calculate the view matrix for use in the graphics shaders.
			 * 
			 * @return A 4x4 Matrix containing the required information to send into shaders.
			 */
			Matrix4x4 calculateViewMatrix();

			/**
			 * @brief Get the Position of the Camera, in world space.
			 * 
			 * @return A Vector3 containing the position of the camera.
			 */
			Vector3 getPosition();

			/**
			 * @brief Get the Direction of the Camera, in world space.
			 * 
			 * @return A Vector3 containing the direction of the camera.
			 */
			Vector3 getDirection();

			bool enabled;

			/**
			 * @brief Update things like position and direction dependant on whether the mouse has moved, or a key has been pressed.
			 * 
			 * @param dt The Delta Time, the time between each frame, so the player moves at the same speed regardless of if they're playing at 100fps or 10fps. 
			 */
			void update(float dt);

		private:
			/// @brief The rotation of the camera.
			Vector3 m_rotation;

			/// @brief The position of the camera.
			Vector3 m_position;

			/// @brief The UP vector of the camera.
			Vector3 m_up;

			/// @brief The direction of the camera.
			Vector3 m_direction;

			/// @brief A pointer to the window object passed as a parameter in the constructor.
			IWindow* m_window;

			/// @brief An object of the CameraControls class, so the Camera can pull the key configurations out of it.
			CameraControls m_controls;
		};

	}
}