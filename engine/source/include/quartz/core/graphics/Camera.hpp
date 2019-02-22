#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/math/Math.hpp>
#include <quartz/core/graphics/IWindow.hpp>
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

			bool onWindowResize(events::WindowResizeEvent event);

			void setProjection(const Matrix4x4& projection);
			Matrix4x4 getProjection() const;

			Matrix4x4 calculateViewMatrix() const;

			void enable(bool enabled);
			bool isEnabled() const { return m_enabled; };

			void tick(float dt);

		private:
			IWindow* m_window;
			
			Matrix4x4 m_projection;
			Vector3 m_rotation;
			Vector3 m_position;
			Vector3 m_up;
			Vector3 m_direction;
			Vector2 m_windowCentre;

			bool m_enabled = true;
		};
	}
}
