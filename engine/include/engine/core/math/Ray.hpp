#pragma once

#include <engine/core/math/Vector3.hpp>

namespace phx
{
	class Ray
	{
	public:
		Ray(const Vector3& start, const Vector3& direction);
		Ray(const Ray& other) = default;
		~Ray() = default;
		
		Vector3 advance(float scale);
		Vector3 backtrace(float scale);

		float getLength() const;

		Vector3 getCurrentPosition() const;

	private:
		float m_length;
		Vector3 m_start, m_direction;
		Vector3 m_currentPosition;
	};
}