#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/math/Vector3.hpp>

using namespace qz::math;

void Vector3::floor()
{
	x = std::floor(x);
	y = std::floor(y);
	z = std::floor(z);
}

void Vector3::ceil()
{
	x = std::ceil(x);
	y = std::ceil(y);
	z = std::ceil(z);
}

void Vector3::normalise()
{
	const float len = std::sqrt(dotProduct({ x, y, z }, { x, y, z }));

	x /= len;
	y /= len;
	z /= len;
}

Vector3 Vector3::cross(const Vector3& vec1, const Vector3& vec2)
{
	return {
	vec1.y * vec2.z - vec1.z * vec2.y,
	vec1.z * vec2.x - vec1.x * vec2.z,
	vec1.x * vec2.y - vec1.y * vec2.x
	};
}

Vector3 Vector3::normalise(const Vector3& vec1)
{
	const float len = std::sqrt(dotProduct(vec1, vec1));

	return {
		vec1.x / len,
		vec1.y / len,
		vec1.z / len
	};
}

float Vector3::dotProduct(const Vector3& vec1, const Vector3& vec2)
{
	return	vec1.x * vec2.x +
		vec1.y * vec2.y +
		vec1.z * vec2.z;
}