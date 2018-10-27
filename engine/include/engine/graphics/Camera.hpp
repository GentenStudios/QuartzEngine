#pragma once

#include "engine/common.hpp"
#include "engine/graphics/IWindow.hpp"

#include "engine/math/MathUtils.hpp"
#include "engine/math/Vector2.hpp"
#include "engine/math/Vector3.hpp"
#include "engine/math/Matrix4x4.hpp"

namespace phx
{
	namespace gfx
	{
		enum class CamDir
		{
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};

		class FPSCam
		{
		public:
			FPSCam(IWindow* window);
			~FPSCam() {};

			void cameraMoveEvent(CamDir direction);
			void cameraLookEvent(float x, float y);

			Matrix4x4 calculateViewMatrix();
			Vector3 getPosition();
			Vector3 getDirection();

			void setDT(float dt) { m_dt = dt; }

			bool enabled;

		private:
			Vector3 m_rotation;
			Vector3 m_position;
			Vector3 m_up;
			Vector3 m_right;
			Vector3 m_direction;

			float m_dt;

			IWindow* m_window;
		};

	}
}