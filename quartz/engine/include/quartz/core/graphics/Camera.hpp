/**
 * @file Camera.hpp
 * @brief File for the Camera Class/Function definitions
 */

#pragma once

#include <quartz/core/math/Vector2.hpp>
#include <quartz/core/math/Vector3.hpp>
#include <quartz/core/math/Matrix4x4.hpp>

#include <quartz/core/graphics/IWindow.hpp>

#include <quartz/core/utils/Config.hpp>
#include <quartz/core/events/Keys.hpp>

namespace qz
{
	namespace gfx
	{
		/**
		 * @brief Class that gets Camera Controls from using the Configuration reader.
		 */
		class CameraControls
		{
		public:
			CameraControls();
			~CameraControls() = default;

			/**
			 * @brief Gets configuration from Camera Controls INI file.
			 */
			void load();

			/**
			 * @brief Gets the key assigned to moving forward.
			 *
			 * @return An events::Keys ENUM value to use straight away in the camera classes.
			 */
			events::Keys moveForward() const;

			/**
			 * @brief Gets the key assigned to moving backwards.
			 *
			 * @return An events::Keys ENUM value to use straight away in the camera classes.
			 */
			events::Keys moveBackwards() const;

			/**
			 * @brief Gets the key assigned to strafing left.
			 *
			 * @return An events::Keys ENUM value to use straight away in the camera classes.
			 */
			events::Keys strafeLeft() const;

			/**
			 * @brief Gets the key assigned to strafing right.
			 *
			 * @return An events::Keys ENUM value to use straight away in the camera classes.
			 */
			events::Keys strafeRight() const;

			/**
			 * @brief Gets the mouse sensitivity from the Config file.
			 *
			 * @return The mouse sensitivity, as a float, ready to use wherever necessary.
			 */
			float mouseSensitivity() const;

			/**
			 * @brief Gets the move speed from the Config file.
			 *
			 * @return The move speed, as a float, ready to use wherever necessary.
			 */
			float moveSpeed() const;

		private:
			/// @brief ConfigFile Object to store the values that are retrieved.
			ConfigFile* m_controlsConfig;
		};

		class FPSCam
		{
		public:
			/**
			 * @brief Constructs a new FPSCam object
			 *
			 * @param window A window object, mainly used to check for key presses.
			 */
			FPSCam(IWindow* window);
			~FPSCam();

			/**
			 * @brief Calculates the view matrix for use in the graphics shaders.
			 *
			 * @return A 4x4 Matrix containing the required information to send into shaders.
			 */
			Matrix4x4 calculateViewMatrix() const;

			/**
			 * @brief Gets the Position of the Camera, in world space.
			 *
			 * @return A Vector3 containing the position of the camera.
			 */
			Vector3 getPosition() const;

			/**
			 * @brief Gets the Direction of the Camera, in world space.
			 *
			 * @return A Vector3 containing the direction of the camera.
			 */
			Vector3 getDirection() const;

			/**
			 * @brief Gets the projection of the Camera.
			 *
			 * @return A Matrix4x4 containing the camera projection.
			 */
			Matrix4x4 getProjection() const;


			/**
			 * @brief Set the projection of the Camera.
			 * @param projection The Matrix4x4 containing the projection.
			 */
			void setProjection(const Matrix4x4& projection);


			/// @brief The status of the camera, whether it's enabled or not.
			bool enabled;

			/**
			 * @brief Updates things like position and direction dependent on whether the mouse has moved, or a key has been pressed.
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

			/// @brief Last position of the mouse.
			TVector2<int> m_windowCentre = TVector2<int>(0, 0);

			/// @brief The projection of the camera.
			Matrix4x4 m_projection;

			/// @brief A pointer to the window object passed as a parameter in the constructor.
			IWindow* m_window;

			/// @brief An object of the CameraControls class, so the Camera can pull the key configurations out of it.
			CameraControls m_controls;
		};

	}
}
