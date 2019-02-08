/**
 * @file MathUtils.hpp
 * @brief MathUtils struct for useful things in life to do with maths :)
 * 
 */

#pragma once

namespace phx
{
	
	/**
	 * @brief Math utility functions.
	 */
	struct MathUtils
	{
		/// @brief The value of PI as a float to 11 decimal places
		static constexpr float PI = 3.14159265359f;

		/**
		 * @brief Converts degrees to radians.
		 * @param degrees The value in degrees to convert to radians
		 * @return The value of the specified degrees in radians
		 */
		template <typename T>
		static T toRadians(const T& degrees)
		{
			return degrees * static_cast<T>(PI / 180.f);
		}

		/**
		 * @brief Converts radians to degrees.
		 * @param radians The value in radians to convert to degrees
		 * @return The value of the specified radians in degrees
		 */
		template <typename T>
		static T toDegrees(const T& radians)
		{
			return radians * static_cast<T>(180.f / PI);
		}

		/**
		 * @brief Clamps a value between the range of min & max (inclusive)
		 * @param value The value to be clamped to the range.
		 * @param min The lower bound to clamp `value` to.
		 * @param max The upper bound to clamp `value` to.
		 * @return The value of `value` clamped to the range `min` and `max`.
		 */
		template <typename T>
		static T clamp(const T& value, const T& min, const T& max)
		{
			return value < min ? min : value > max ? max : value;
		}
	};

}
