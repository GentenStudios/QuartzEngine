// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <Quartz/Math/MathUtils.hpp>
#include <Quartz/Math/Matrix4x4.hpp>
#include <Quartz/QuartzPCH.hpp>

#define INDEX_2D(x, y) x + (y * 4)

using namespace qz::math;

Matrix4x4::Matrix4x4() { setIdentity(); }

void Matrix4x4::setIdentity()
{
	for (float& element : elements)
		element = 0.f;

	// Generates identity matrix.
	elements[INDEX_2D(0, 0)] = 1.f;
	elements[INDEX_2D(1, 1)] = 1.f;
	elements[INDEX_2D(2, 2)] = 1.f;
	elements[INDEX_2D(3, 3)] = 1.f;
}

Matrix4x4::Matrix4x4(float m00, float m10, float m20, float m30, float m01,
                     float m11, float m21, float m31, float m02, float m12,
                     float m22, float m32, float m03, float m13, float m23,
                     float m33)
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

Matrix4x4 Matrix4x4::perspective(const float& aspectRatio,
                                 const float& fieldOfView,
                                 const float& farPlane, const float& nearPlane)
{
	Matrix4x4 perspectMatrix;

	for (float& element : perspectMatrix.elements)
		element = 0.f;

	const float fieldOfViewRadians = degreeToRadians(fieldOfView);
	const float tangentFoVHalf     = std::tan(fieldOfViewRadians / 2.f);

	perspectMatrix.elements[0] = 1.f / (aspectRatio * tangentFoVHalf);
	perspectMatrix.elements[INDEX_2D(1, 1)] = 1.f / tangentFoVHalf;
	perspectMatrix.elements[INDEX_2D(2, 2)] =
	    -(farPlane + nearPlane) / (farPlane - nearPlane);
	perspectMatrix.elements[INDEX_2D(3, 2)] = -1.f;
	perspectMatrix.elements[INDEX_2D(2, 3)] =
	    -(2.f * farPlane * nearPlane) / (farPlane - nearPlane);

	return perspectMatrix;
}

Matrix4x4 Matrix4x4::ortho(float left, float right, float top, float bottom,
                           float farPlane, float nearPlane)
{
	Matrix4x4 out;

	for (float& element : out.elements)
		element = 0.f;

	out.elements[0]              = 2.f / (right - left);
	out.elements[INDEX_2D(1, 1)] = 2.f / (top - bottom);
	out.elements[INDEX_2D(2, 2)] = -2.f / (farPlane - nearPlane);
	out.elements[INDEX_2D(3, 3)] = 1.f;
	out.elements[INDEX_2D(0, 3)] = -((right + left) / (right - left));
	out.elements[INDEX_2D(1, 3)] = -((top + bottom) / (top - bottom));
	out.elements[INDEX_2D(2, 3)] =
	    -((farPlane + nearPlane) / (farPlane - nearPlane));

	return out;
}

Matrix4x4 Matrix4x4::lookAt(const Vector3& eyePos, const Vector3& centre,
                            const Vector3& up)
{
	Vector3 f = centre - eyePos;
	f.normalize();

	Vector3 s = Vector3::cross(f, up);
	s.normalize();

	const Vector3 u = Vector3::cross(s, f);

	const Matrix4x4 lookAtMatrix(
	    s.x, u.x, -f.x, 0.f, s.y, u.y, -f.y, 0.f, s.z, u.z, -f.z, 0.f,
	    -Vector3::dotProduct(s, eyePos), -Vector3::dotProduct(u, eyePos),
	    Vector3::dotProduct(f, eyePos), 1.f);

	return lookAtMatrix;
}

// #todo: could these two not share the same code & not need to duplicate?
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
	const float x = elements[0 + 0 * 4] * other.x +
	                elements[1 + 0 * 4] * other.y +
	                elements[2 + 0 * 4] * other.z;
	const float y = elements[0 + 1 * 4] * other.x +
	                elements[1 + 1 * 4] * other.y +
	                elements[2 + 1 * 4] * other.z;
	const float z = elements[0 + 2 * 4] * other.x +
	                elements[1 + 2 * 4] * other.y +
	                elements[2 + 2 * 4] * other.z;

	return {x, y, z};
}
