#pragma once

#include "engine/common.hpp"
#include "engine/graphics/IWindow.hpp"

#include "engine/math/MathUtils.hpp"
#include "engine/math/Vector2.hpp"
#include "engine/math/Vector3.hpp"
#include "engine/math/Matrix4x4.hpp"

#include "engine/utils/Config.hpp"

namespace phx
{
	namespace gfx
	{
		class CameraControls
		{
		public:
			void load();

			SDL_Scancode moveForward();
			SDL_Scancode moveBackwards();
			SDL_Scancode strafeLeft();
			SDL_Scancode strafeRight();

			float mouseSensitivity();
			float moveSpeed();

		private:
			ConfigFile * m_controlsConfig;
		};

		class FPSCam
		{
		public:
			FPSCam(IWindow* window);
			~FPSCam() {};

			Matrix4x4 calculateViewMatrix();
			Vector3 getPosition();
			Vector3 getDirection();

			bool enabled;

			void update(float dt);

		private:
			Vector3 m_rotation;
			Vector3 m_position;
			Vector3 m_up;
			Vector3 m_direction;

			IWindow* m_window;

			CameraControls m_controls;
		};

	}
}