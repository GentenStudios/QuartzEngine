#include <engine/core/math/Matrix4x4.hpp>

#include <cstring>
#include <cmath>

using namespace phx;

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
	for (int i = 0; i < 16; i++) mat4.elements[i] = 0.f;

	float fovr = MathUtils::toRadians(fov);

	float tanHalfFovy = std::tan(fovr / 2.f);

	mat4.elements[0] = 1.f / (aspect * tanHalfFovy);
	mat4.elements[INDEX2D(1, 1)] = 1.f / tanHalfFovy;
	mat4.elements[INDEX2D(2, 2)] = -(far + near) / (far - near);
	mat4.elements[INDEX2D(3, 2)] = -1.f;
	mat4.elements[INDEX2D(2, 3)] = -(2.f * far * near) / (far - near);
	return mat4;
}

Matrix4x4 Matrix4x4::ortho(float left, float right, float top, float bottom, float far, float near)
{
	Matrix4x4 out;
	for (int i = 0; i < 16; i++) out.elements[i] = 0.f;

	out.elements[0] = 2.f / (right - left);
	out.elements[INDEX2D(1, 1)] = 2.f / (top - bottom);
	out.elements[INDEX2D(2, 2)] = -2.f / (far - near);
	out.elements[INDEX2D(3, 3)] = 1.f;
	out.elements[INDEX2D(0, 3)] = -((right + left) / (right - left));
	out.elements[INDEX2D(1, 3)] = -((top + bottom) / (top - bottom));
	out.elements[INDEX2D(2, 3)] = -((far + near) / (far - near));

	return out;
}

Matrix4x4::Matrix4x4(
	float m00, float m10, float m20, float m30,
	float m01, float m11, float m21, float m31,
	float m02, float m12, float m22, float m32,
	float m03, float m13, float m23, float m33
)
{
	elements[0 + 0 * 4] = m00;
	elements[1 + 0 * 4] = m10;
	elements[2 + 0 * 4] = m20;
	elements[3 + 0 * 4] = m30;

	elements[0 + 1 * 4] = m01;
	elements[1 + 1 * 4] = m11;
	elements[2 + 1 * 4] = m21;
	elements[3 + 1 * 4] = m31;

	elements[0 + 2 * 4] = m02;
	elements[1 + 2 * 4] = m12;
	elements[2 + 2 * 4] = m22;
	elements[3 + 2 * 4] = m32;

	elements[0 + 3 * 4] = m03;
	elements[1 + 3 * 4] = m13;
	elements[2 + 3 * 4] = m23;
	elements[3 + 3 * 4] = m33;
}

Matrix4x4 Matrix4x4::lookAt(const Vector3& eye, const Vector3& centre, const Vector3& up)
{
	Vector3 f = Vector3::normalize(centre - eye);
	Vector3 s = Vector3::normalize(Vector3::cross(f, up));
	Vector3 u = Vector3::cross(s, f);

	Matrix4x4 lookAtMatrix(
		s.x, u.x, -f.x, 0.f,
		s.y, u.y, -f.y, 0.f,
		s.z, u.z, -f.z, 0.f,
		-Vector3::dot(s, eye), -Vector3::dot(u, eye), Vector3::dot(f, eye), 1.f
	);

	return lookAtMatrix;
}

Matrix4x4 phx::operator*(const Matrix4x4& left, const Matrix4x4& right)
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

Matrix4x4 phx::operator*(const Matrix4x4& left, const float& right)
{
	Matrix4x4 matrix;
	for (int i = 0; i < 16; i++)
	{
		matrix.elements[i] = left.elements[i] * right;
	}
	return matrix;
}

Vector3 phx::operator*(const Matrix4x4& left, const Vector3& right)
{
	float x = left.elements[0 + 0 * 4] * right.x + left.elements[1 + 0 * 4] * right.y + left.elements[2 + 0 * 4] * right.z;
	float y = left.elements[0 + 1 * 4] * right.x + left.elements[1 + 1 * 4] * right.y + left.elements[2 + 1 * 4] * right.z;
	float z = left.elements[0 + 2 * 4] * right.x + left.elements[1 + 2 * 4] * right.y + left.elements[2 + 2 * 4] * right.z;

	return { x, y, z };
}
