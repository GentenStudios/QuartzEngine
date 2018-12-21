#include <engine/core/math/Vector3.hpp>

#include <cmath>

using namespace phx;

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

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

Vector3 Vector3::normalize(const Vector3& a)
{
	float len = std::sqrt(dot(a, a));

	return {
		a.x / len,
		a.y / len,
		a.z / len
	};
}

float Vector3::dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

void Vector3::floor()
{
	x = std::floor(x);
	y = std::floor(y);
	z = std::floor(z);
}

void Vector3::toFloorOrNotToFloorThatIsTheQuestion()
{
	if (x < 0)
		x = std::ceil(x);
	else
		x = std::floor(x);

	if (x < 0)
		y = std::ceil(y);
	else
		y = std::floor(y);

	if (z < 0)
		z = std::ceil(z);
	else
		z = std::floor(z);
}

void Vector3::set(const float& a)
{
	this->x = a;
	this->y = a;
	this->z = a;
}

void Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

Vector3 phx::operator+(const Vector3& left, const Vector3& right)
{
	return {
		left.x + right.x,
		left.y + right.y,
		left.z + right.z
	};
}

Vector3 phx::operator-(const Vector3& left, const Vector3& right)
{
	return {
		left.x - right.x,
		left.y - right.y,
		left.z - right.z
	};
}

Vector3 phx::operator*(const Vector3& left, const Vector3& right)
{
	return {
		left.x * right.x,
		left.y * right.y,
		left.z * right.z
	};
}

Vector3 phx::operator/(const Vector3& left, const Vector3& right)
{
	return {
		left.x / right.x,
		left.y / right.y,
		left.z / right.z
	};
}

bool phx::operator==(const Vector3& left, const Vector3& right)
{
	return (
		left.x == right.x &&
		left.y == right.y &&
		left.z == right.z
	);
}

bool phx::operator!=(const Vector3& left, const Vector3& right)
{
	return !(
		left.x == right.x &&
		left.y == right.y &&
		left.z == right.z
	);
}