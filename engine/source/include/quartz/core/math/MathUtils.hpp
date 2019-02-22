#pragma once

#include <algorithm>

namespace qz
{
	namespace math
	{
		/**
		 * @brief A Utility providing PI to 11 decimal places.
		 */
		static constexpr float PI = 3.14159265359f;

		/**
		 * @brief Converts degrees to radians.
		 * @param degrees The number of degrees waiting to be converted.
		 * @return The converted value, in radians.
		 */
		static float degreeToRadians(const float& degrees)
		{
			return degrees * PI / 180.f;
		}

		/**
		 * @brief Converts radians to degrees.
		 * @param radians The number of radians waiting to be converted.
		 * @return The converted value, in degrees.
		 */
		static float radianToDegrees(const float& radians)
		{
			return radians * 180.f / PI;
		}

		/**
		 * @brief 
		 * @tparam T The data type that needs to be clamped.
		 * @param n The actual value needing to be clamped.
		 * @param lower The lowest value the result should be allowed to be.
		 * @param upper The highest value the results should be allowed to be.
		 * @return Either the original number if the value is between the lower and upper bounds, OR the upper/lower bounds dependant
		 *		on the value.
		 */
		template <typename T>
		T clamp(const T& n, const T& lower, const T& upper) {
			return std::max(lower, std::min(n, upper));
		}
	};
}
