#include "engine/math/Vector2.hpp"

using namespace phx;

Vector2::Vector2()
	: x(0.f), y(0.f)
{
}

Vector2::Vector2(const float& x, const float& y)
	: x(x), y(y)
{
}

Vector2::Vector2(const float& a)
	: x(a), y(a)
{
}