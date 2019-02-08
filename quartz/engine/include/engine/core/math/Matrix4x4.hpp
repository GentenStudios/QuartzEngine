/**
 * @file Matrix4x4.hpp
 * @brief 4 by 4 Matrix for fun maths! :/ or :) depending on the day.
 * 
 */

#pragma once

#include <engine/core/math/Vector3.hpp>

namespace phx {

	/**
	 * @brief Represents a column major 4x4 matrix of floats.
	 */
	struct Matrix4x4
	{
		float elements[4 * 4]; ///< The 16 float array that stores the matrices elements sequentially.

		/**
		 * @brief Default constructs the as an identity matrix (the top left to bottom right diagonal is 1.0f)
		 */
		Matrix4x4();

		Matrix4x4(
			float m00, float m10, float m20, float m30,
			float m01, float m11, float m21, float m31,
			float m02, float m12, float m22, float m32,
			float m03, float m13, float m23, float m33
		);

		/**
		 * @brief Constructs a perspective projection matrix.
		 * @param aspect The aspect ratio is the ratio of x (width) to y (height).
		 * @param fov Specifies the field of view angle, in degrees.
		 * @param far Distance from the viewer to the far clipping plane (should always be positive)
		 * @param near Distance from the viewer to the near clipping plane.
		 * @return The calculated perspective projection matrix.
		 */
		static Matrix4x4 perspective(float aspect, float fov, float far, float near);

		/**
		 * @brief 
		 * @param left 
		 * @param right 
		 * @param top 
		 * @param bottom 
		 * @param far 
		 * @param near 
		 * @return 
		 */
		static Matrix4x4 ortho(float left, float right, float top, float bottom, float far, float near);


		/**
		 * @brief 
		 * @param eye 
		 * @param centre 
		 * @param up 
		 * @return 
		 */
		static Matrix4x4 lookAt(const Vector3& eye, const Vector3& centre, const Vector3& up);
	};

	/**
	 * @brief Multiplies two matrices together. Multiplication is not commutative (therefore left*right != right*left)
	 * @param left Left hand side of matrix multiplication.
	 * @param right Right hand side of matrix multiplication.
	 * @return Product of `left` and `right` matrices.
	 */
	Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right);

	/**
	 * @brief Multiplies together a matrix and a scalar value.
	 * @param left Left hand side of multiplication.
	 * @param right Right hand side of multiplication
	 * @return Product of `left` and `right`
	 */
	Matrix4x4 operator*(const Matrix4x4& left, const float& right);

	/**
	 * @brief Multiplies together a matrix and a Vector3 value.
	 * @param left Left hand side of multiplication.
	 * @param right Right hand side of multiplication.
	 * @return Product of `left` and `right`
	 */
	Vector3 operator*(const Matrix4x4& left, const Vector3& right);

}
