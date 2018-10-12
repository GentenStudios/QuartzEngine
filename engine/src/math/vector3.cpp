#include "engine/math/vector3.hpp"

using namespace phoenix;

Vector3::Vector3(const float& x, const float& y, const float& z) : 
	x(x), y(y), z(z)
{
}

Vector3::Vector3(const float& a) :
	x(a), y(a), z(a) 
{
}

Vector3::Vector3() :
	x(0.f), y(0.f), z(0.f)
{
}

Vector3 operator+(const Vector3& left, const Vector3& right)
{
	return {
		left.x + right.x,
		left.y + right.y,
		left.z + right.z
	};
}

Vector3 operator-(const Vector3& left, const Vector3& right)
{
	return {
		left.x - right.x,
		left.y - right.y,
		left.z - right.z
	};
}

Vector3 operator*(const Vector3& left, const Vector3& right)
{
	return {
		left.x * right.x,
		left.y * right.y,
		left.z * right.z
	};
}

Vector3 operator/(const Vector3& left, const Vector3& right)
{
	return {
		left.x / right.x,
		left.y / right.y,
		left.z / right.z
	};
}
