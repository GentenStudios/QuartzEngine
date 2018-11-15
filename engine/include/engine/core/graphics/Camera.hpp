#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/math/Vector2.hpp>
#include <engine/core/math/Vector3.hpp>
#include <engine/core/math/Matrix4x4.hpp>
#include <engine/core/math/MathUtils.hpp>

#include <engine/core/graphics/IWindow.hpp>
#include <SDL.h>

namespace phx
{
	namespace gfx
	{
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
		};

	}
}