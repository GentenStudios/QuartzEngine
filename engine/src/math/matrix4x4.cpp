#include "engine/math/matrix4x4.hpp"

#include "engine/math/mathutils.hpp"

#include <cstring>
#include <cmath>

using namespace phoenix;

#define INDEX2D(x, y) (x + y * 4)

Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < 4 * 4; ++i) elements[i] = 0.f;

	elements[INDEX2D(0, 0)] = 1.f;
	elements[INDEX2D(1, 1)] = 1.f;
	elements[INDEX2D(2, 2)] = 1.f;
	elements[INDEX2D(3, 3)] = 1.f;
}

Matrix4x4 Matrix4x4::perspective(float aspect, float fov, float far, float near)
{
	Matrix4x4 mat4;

	float t = -(2.f * far * near) / (far - near);
	float tanHalfFovy = std::tanf(MathUtils::toRadians(fov * 0.5f));

	mat4.elements[0] = 1.f / (aspect * tanHalfFovy);
	mat4.elements[INDEX2D(1, 1)] = 1.f / tanHalfFovy;
	mat4.elements[INDEX2D(2, 2)] = -(far + near) / (far - near);
	mat4.elements[INDEX2D(3, 2)] = -1.f;
	mat4.elements[INDEX2D(2, 3)] = -(2.f * far * near) / (far - near);
	mat4.elements[INDEX2D(3, 3)] = 0.f;

	return mat4;
}

Matrix4x4 phoenix::operator*(const Matrix4x4& left, const Matrix4x4& right)
{
	Matrix4x4 matrix;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			float xy = 0.f;
			for (int k = 0; k < 4; ++k)
			{
				xy += left.elements[INDEX2D(x, k)] * right.elements[INDEX2D(k, y)];
			}
			matrix.elements[INDEX2D(x, y)] = xy;
		}
	}

	return matrix;
}

Matrix4x4 phoenix::operator*(const Matrix4x4& left, const float& right)
{
	Matrix4x4 matrix;
	for (int i = 0; i < 16; i++)
	{
		matrix.elements[i] = left.elements[i] * right;
	}
	return matrix;
}

Vector3 phoenix::operator*(const Matrix4x4& left, const Vector3& right)
{
	float x = left.elements[0 + 0 * 4] * right.x + left.elements[1 + 0 * 4] * right.y + left.elements[2 + 0 * 4] * right.z;
	float y = left.elements[0 + 1 * 4] * right.x + left.elements[1 + 1 * 4] * right.y + left.elements[2 + 1 * 4] * right.z;
	float z = left.elements[0 + 2 * 4] * right.x + left.elements[1 + 2 * 4] * right.y + left.elements[2 + 2 * 4] * right.z;

	return { x, y, z };
}
