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
		class CameraControls
		{
		public:
			void load();

			events::Keys moveForward();
			events::Keys moveBackwards();
			events::Keys strafeLeft();
			events::Keys strafeRight();

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