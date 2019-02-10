/**
 * @file Vector2.hpp
 * @brief 2 Component Vector for absolute fun. Yay?
 * 
 */

#pragma once

namespace qz
{
	struct Vector2 {
		float x;
		float y;

		Vector2();
		Vector2(const float& x, const float& y);
		Vector2(const float& a);
	};

	template <typename T>
	struct TVector2 {
		T x, y;

		TVector2(const T& x, const T& y) : x(x), y(y) {}
	};
}
