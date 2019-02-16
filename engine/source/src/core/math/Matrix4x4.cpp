#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/math/Matrix4x4.hpp>
#include <quartz/core/math/MathUtils.hpp>

#define INDEX_2D(x, y) x + (y * 4)

using namespace qz::math;

Matrix4x4::Matrix4x4()
{
	for (float& element : elements) element = 0.f;

	// Generates identity matrix.
	elements[INDEX_2D(0, 0)] = 1.f;
	elements[INDEX_2D(1, 1)] = 1.f;
	elements[INDEX_2D(2, 2)] = 1.f;
	elements[INDEX_2D(3, 3)] = 1.f;
}

Matrix4x4::Matrix4x4(const float e0, const float e4, const float e8, const float e12,
 					 const float e1, const float e5, const float e9,  const float e13,
					 const float e2, const float e6, const float e10, const float e14,
					 const float e3, const float e7, const float e11, const float e15
)
{
	elements[0 + 0 * 4] = e0;
	elements[1 + 0 * 4] = e1;
	elements[2 + 0 * 4] = e2;
	elements[3 + 0 * 4] = e3;

	elements[0 + 1 * 4] = e4;
	elements[1 + 1 * 4] = e5;
	elements[2 + 1 * 4] = e6;
	elements[3 + 1 * 4] = e7;

	elements[0 + 2 * 4] = e8;
	elements[1 + 2 * 4] = e9;
	elements[2 + 2 * 4] = e10;
	elements[3 + 2 * 4] = e11;

	elements[0 + 3 * 4] = e12;
	elements[1 + 3 * 4] = e13;
	elements[2 + 3 * 4] = e14;
	elements[3 + 3 * 4] = e15;
}

Matrix4x4 Matrix4x4::perspective(const float& aspectRatio, const float& fieldOfView, const float& farPlane,
	const float& nearPlane)
{
	Matrix4x4 perspectMatrix;
	for (float& element : perspectMatrix.elements) element = 0.f;

	const float fieldOfViewRadians = degreeToRadians(fieldOfView);

	const float tangentFoVHalf = std::tan(fieldOfViewRadians / 2.f);

	perspectMatrix.elements[0] = 1.f / (aspectRatio * tangentFoVHalf);
	perspectMatrix.elements[INDEX_2D(1, 1)] = 1.f / tangentFoVHalf;
	perspectMatrix.elements[INDEX_2D(2, 2)] = -(farPlane + nearPlane) / (farPlane - nearPlane);
	perspectMatrix.elements[INDEX_2D(3, 2)] = -1.f;
	perspectMatrix.elements[INDEX_2D(2, 3)] = -(2.f * farPlane * nearPlane) / (farPlane - nearPlane);

	return perspectMatrix;
}

Matrix4x4 Matrix4x4::ortho(float left, float right, float top, float bottom, float farPlane, float nearPlane)
{
	Matrix4x4 out;
	for (float& element : out.elements) element = 0.f;

	out.elements[0] = 2.f / (right - left);
	out.elements[INDEX_2D(1, 1)] = 2.f / (top - bottom);
	out.elements[INDEX_2D(2, 2)] = -2.f / (farPlane - nearPlane);
	out.elements[INDEX_2D(3, 3)] = 1.f;
	out.elements[INDEX_2D(0, 3)] = -((right + left) / (right - left));
	out.elements[INDEX_2D(1, 3)] = -((top + bottom) / (top - bottom));
	out.elements[INDEX_2D(2, 3)] = -((farPlane + nearPlane) / (farPlane - nearPlane));

	return out;
}

Matrix4x4 Matrix4x4::lookAt(const Vector3& eyePos, const Vector3& centre, const Vector3& up)
{
	Vector3 f = centre - eyePos;
	f.normalise();

	Vector3 s = Vector3::cross(f, up);
	s.normalise();

	const Vector3 u = Vector3::cross(s, f);

	Matrix4x4 lookAtMatrix(
		s.x, u.x, -f.x, 0.f,
		s.y, u.y, -f.y, 0.f,
		s.z, u.z, -f.z, 0.f,
		-Vector3::dotProduct(s, eyePos), -Vector3::dotProduct(u, eyePos), Vector3::dotProduct(f, eyePos), 1.f
	);

	return lookAtMatrix;
}

void Matrix4x4::operator*=(const Matrix4x4& other)
{
	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			float xy = 0.f;

			for (int k = 0; k < 4; ++k)
			{
				xy += elements[INDEX_2D(x, k)] * other.elements[INDEX_2D(k, y)];
			}

			elements[INDEX_2D(x, y)] = xy;
		}
	}
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other)
{
	Matrix4x4 mat4;

	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			float xy = 0.f;

			for (int k = 0; k < 4; ++k)
			{
				xy += elements[INDEX_2D(x, k)] * other.elements[INDEX_2D(k, y)];
			}

			mat4.elements[INDEX_2D(x, y)] = xy;
		}
	}

	return mat4;
}

void Matrix4x4::operator*=(const float& other)
{
	for (float& element : elements)
	{
		element *= other;
	}
}

Matrix4x4 Matrix4x4::operator*(const float& other)
{
	Matrix4x4 matrix;
	for (int i = 0; i < 16; i++)
	{
		matrix.elements[i] = elements[i] * other;
	}
	return matrix;
}

Vector3 Matrix4x4::operator*(const Vector3& other)
{
	const float x = elements[0 + 0 * 4] * other.x + elements[1 + 0 * 4] * other.y + elements[2 + 0 * 4] * other.z;
	const float y = elements[0 + 1 * 4] * other.x + elements[1 + 1 * 4] * other.y + elements[2 + 1 * 4] * other.z;
	const float z = elements[0 + 2 * 4] * other.x + elements[1 + 2 * 4] * other.y + elements[2 + 2 * 4] * other.z;

	return { x, y, z };
}
