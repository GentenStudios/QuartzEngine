#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/math/Math.hpp>
#include <quartz/core/graphics/IWindow.hpp>

#include <quartz/core/events/KeyEvent.hpp>
#include <quartz/core/events/MouseEvent.hpp>
#include <quartz/core/events/ApplicationEvent.hpp>

namespace qz
{
	namespace gfx
	{
		class QZ_API FPSCamera
		{
		public:
			FPSCamera(IWindow* window);

			Vector3 getPosition() const;
			Vector3 getDirection() const;

			void setProjection(const Matrix4x4& projection);
			Matrix4x4 getProjection() const;

			Matrix4x4 calculateViewMatrix() const;

			void enable(bool enabled) { m_enabled = enabled; }
			bool isEnabled() const { return m_enabled; };

			void tick(float dt);

		private:
			IWindow* m_window;
			
			Matrix4x4 m_projection;
			Vector3 m_rotation;
			Vector3 m_position;
			Vector3 m_up;
			Vector3 m_right;
			Vector3 m_direction;
			Vector2 m_windowCentre = { 0, 0 };

			bool m_enabled = true;

			// Set the initial Delta Time to 0.16 as that's the delta time if an application is run at 60fps.
			float m_dt = 0.16f;
		};
	}
}
