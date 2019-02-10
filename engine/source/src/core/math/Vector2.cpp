#include <quartz/core/quartz-pch.hpp>
#include <quartz/core/math/Vector2.hpp>

using namespace qz::math;

void Vector2::floor()
{
	x = std::floor(x);
	y = std::floor(y);
}

void Vector2::ceil()
{
	x = std::ceil(x);
	y = std::ceil(y);
}
