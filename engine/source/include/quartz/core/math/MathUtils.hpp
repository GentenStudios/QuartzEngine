#pragma once

#include <algorithm>

namespace qz
{
	namespace math
	{
		static constexpr float PI = 3.14159265359f;

		static float degreeToRadians(const float& degrees)
		{
			return degrees * PI / 180.f;
		}

		static float radianToDegrees(const float& radians)
		{
			return radians * 180.f / PI;
		}

		template <typename T>
		T clamp(const T& n, const T& lower, const T& upper) {
			return std::max(lower, std::min(n, upper));
		}
	};
}
