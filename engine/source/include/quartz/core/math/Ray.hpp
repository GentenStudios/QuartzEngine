#pragma once

#include <quartz/core/math/Vector3.hpp>

namespace qz
{
	namespace math
	{
		/**
		 * @brief Produces a castable ray for helping find things at positions/intervals along the ray.
		 */
		class Ray
		{
		public:
			/**
			 * @brief Constructs a Ray object.
			 * @param start The position of the start of the ray.
			 * @param direction The direction the ray is "traveling" in.
			 */
			Ray(const Vector3& start, const Vector3& direction);

			Ray(const Ray& other) = default;
			~Ray() = default;

			/**
			 * @brief Advances along a ray.
			 * @param scale The distance to advance along the ray
			 * @return The new position along the ray.
			 */
			Vector3 advance(float scale);

			/**
			 * @brief Backtracks (goes backwards) along a ray.
			 * @param scale The distance to backtrack along the ray.
			 * @return The new position along the ray.
			 */
			Vector3 backtrace(float scale);

			/**
			 * @brief Gets the current length of the ray.
			 * @return The length of the ray.
			 */
			float getLength() const;

			/**
			 * @brief Gets the current position along the ray.
			 * @return The current position along the ray
			 */
			Vector3 getCurrentPosition() const;

		private:
			float m_length;
			Vector3 m_start;
			Vector3 m_direction;
			Vector3 m_currentPosition;
		};
	}
}