#pragma once

#include "engine/math/Vector3.hpp"

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

		static Matrix4x4 lookAt(const Vector3& eye, const Vector3& centre, const Vector3& up);
	};

	/**
	 * @brief Multiplys two matrices together. Multiplication is not commutative (therefore left*right != right*left)
	 * @param left Left hand side of matrix multiplication.
	 * @param right Right hand side of matrix multiplication.
	 * @return Product of `left` and `right` matrices.
	 */
	Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right);

	/**
	 * @brief Multiplys together a matrix and a scalar value.
	 * @param left Left hand side of multiplication.
	 * @param right Right hand side of multiplication
	 * @return Product of `left` and `right`
	 */
	Matrix4x4 operator*(const Matrix4x4& left, const float& right);

	/**
	 * @brief Multipys together a matrix and a Vector3 value.
	 * @param left Left hand side of multiplication.
	 * @param right Right hand side of multiplication.
	 * @return Product of `left` and `right`
	 */
	Vector3 operator*(const Matrix4x4& left, const Vector3& right);

}
