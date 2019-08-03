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

#pragma once

#include <Quartz/Math/Vector3.hpp>

namespace qz
{
	namespace math
	{

		/**
		 * @brief Represents a column major 4x4 Matrix of floats.
		 */
		struct Matrix4x4
		{
			/// @brief The 16 float array that stores the matrix's elements
			/// sequentially.
			float elements[16];

			/**
			 * @brief Default constructs the as an identity matrix (the top left
			 * to bottom right diagonal is 1.0f)
			 */
			Matrix4x4();

			Matrix4x4(float m00, float m10, float m20, float m30, float m01,
			          float m11, float m21, float m31, float m02, float m12,
			          float m22, float m32, float m03, float m13, float m23,
			          float m33);

			void setIdentity();

			~Matrix4x4() = default;

			/**
			 * @brief Constructs a perspective projection matrix.
			 * @param aspectRatio The aspect ratio is the ratio of x (width) to
			 * y (height).
			 * @param fieldOfView Specifies the field of view angle, in degrees.
			 * @param farPlane Distance from the viewer to the far clipping
			 * plane (should always be positive)
			 * @param nearPlane Distance from the viewer to the near clipping
			 * plane.
			 * @return The calculated perspective projection matrix.
			 */
			static Matrix4x4 perspective(const float& aspectRatio,
			                             const float& fieldOfView,
			                             const float& farPlane,
			                             const float& nearPlane);

			/**
			 * @brief
			 * @param left
			 * @param right
			 * @param top
			 * @param bottom
			 * @param farPlane
			 * @param nearPlane
			 * @return
			 */
			static Matrix4x4 ortho(float left, float right, float top,
			                       float bottom, float farPlane,
			                       float nearPlane);

			/**
			 * @brief Calculates a "view" matrix, so where a user is looking,
			 * mainly designed for the camera to use.
			 * @param eyePos The position of the eye, e.g. the camera's position
			 * @param centre The place that is being looked at. The centre of
			 * the view.
			 * @param up The up vector, so basically saying "which direction is
			 * up".
			 * @return The calculated view matrix.
			 */
			static Matrix4x4 lookAt(const Vector3& eyePos,
			                        const Vector3& centre, const Vector3& up);

			/// @brief Operator Overload for multiplying an established lvalue
			/// matrix object with another matrix.
			void operator*=(const Matrix4x4& other);

			/// @brief Operator Overload for multiplying a matrix object
			/// (lvalue, or rvalue) with another matrix.
			Matrix4x4 operator*(const Matrix4x4& other);

			/// @brief Operator Overload for multiplying an established lvalue
			/// matrix object with scalar value, a float.
			void operator*=(const float& other);

			/// @brief Operator Overload for multiplying a matrix object
			/// (lvalue, or rvalue) with scalar value, a float.
			Matrix4x4 operator*(const float& other);

			/**
			 * @brief Operator Overload for multiplying a matrix object (lvalue
			 * or rvalue) with a 3 component Vector.
			 * @return The calculated product, as a Vector3, a 3 component
			 * vector.
			 */
			Vector3 operator*(const Vector3& other);
		};
	}; // namespace math
} // namespace qz
