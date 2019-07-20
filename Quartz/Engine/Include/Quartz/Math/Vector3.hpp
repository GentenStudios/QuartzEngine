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

#include <cmath>

namespace qz
{
	namespace math
	{
		/**
		 * @brief A 3 Component Vector. Simplifies maths, and management of
		 * parameters.
		 */
		struct Vector3
		{
			union {
				float x;
				float r;
			};

			union {
				float y;
				float g;
			};

			union {
				float z;
				float b;
			};

			/**
			 * @brief Default constructs a 3 component Vector, initializes all
			 * components to 0.
			 */
			Vector3 () : x (0), y (0), z (0) {}

			/**
			 * @brief Constructs a 3 component Vector.
			 * @param x The value that all components should be set to.
			 */
			Vector3 (const float x) : x (x), y (x), z (x) {}

			/**
			 * @brief Constructs a 3 component Vector.
			 * @param x The value that the X component should be set to.
			 * @param y The value that the Y component should be set to.
			 * @param z The value that the Z component should be set to.
			 */
			Vector3 (const float x, const float y, const float z)
			    : x (x), y (y), z (z)
			{
			}

			/**
			 * @brief Sets all components in the vector to a scalar value.
			 * @param scalar The value to set all components to.
			 */
			void set (const float scalar)
			{
				x = scalar;
				y = scalar;
				z = scalar;
			}

			/**
			 * @brief Floors all components in the Vector.
			 *
			 * Flooring (simply put) is the process of rounding down each
			 * component to the nearest integer.
			 */
			void floor ();

			/**
			 * @brief Ceils all components in the Vector.
			 *
			 * Ceiling (simply put) is the process of rounding up each component
			 * to the nearest integer.
			 */
			void ceil ();

			/**
			 * @brief Normalizes the vector.
			 *
			 * Normalization is a mathematical process, to find out more about
			 * it, read it up on the internet.
			 */
			void normalize ();

			/**
			 * @brief Crosses two vectors.
			 * @param vec1 The first vector to cross.
			 * @param vec2 The second vector to cross.
			 * @return The crossed product.
			 */
			static Vector3 cross (const Vector3& vec1, const Vector3& vec2);

			/**
			 * @brief Normalizes a vector.
			 * @param vec1 The vector to normalize
			 * @return The normalized vector.
			 *
			 * Normalization is a mathematical process, to find out more about
			 * it, read it up on the internet.
			 */
			static Vector3 normalize (const Vector3& vec1);

			/**
			 * @brief Calculates the Dot Product of two vectors.
			 * @param vec1 The first vector in the calculation.
			 * @param vec2 The second vector in the calculation.
			 * @return The calculated product.
			 */
			static float dotProduct (const Vector3& vec1, const Vector3& vec2);

			///////////////////// OPERATOR OVERLOADS /////////////////////

			void operator+= (const Vector3& other)
			{
				x += other.x;
				y += other.y;
				z += other.z;
			}

			void operator-= (const Vector3& other)
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
			}

			void operator+= (const float& i)
			{
				x += i;
				y += i;
				z += i;
			}

			void operator-= (const float& i)
			{
				x -= i;
				y -= i;
				z -= i;
			}

			Vector3 operator+ (const Vector3& other) const
			{
				return Vector3 (x + other.x, y + other.y, z + other.z);
			}

			Vector3 operator- (const Vector3& other) const
			{
				return Vector3 (x - other.x, y - other.y, z - other.z);
			}

			Vector3 operator+ (const float& i) const
			{
				return Vector3 (x + i, y + i, z + i);
			}

			Vector3 operator- (const float& i) const
			{
				return Vector3 (x - i, y - i, z - i);
			}

			void operator*= (const Vector3& other)
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
			}

			void operator/= (const Vector3& other)
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
			}

			void operator*= (const float& scalar)
			{
				x *= scalar;
				y *= scalar;
				z *= scalar;
			}

			void operator/= (const float& scalar)
			{
				x /= scalar;
				y /= scalar;
				z /= scalar;
			}

			Vector3 operator* (const Vector3& other) const
			{
				return Vector3 (x * other.x, y * other.y, z * other.z);
			}

			Vector3 operator/ (const Vector3& other) const
			{
				return Vector3 (x / other.x, y / other.y, z / other.z);
			}

			Vector3 operator* (const float& scalar) const
			{
				return Vector3 (x * scalar, y * scalar, z * scalar);
			}

			Vector3 operator/ (const float& scalar) const
			{
				return Vector3 (x / scalar, y / scalar, z / scalar);
			}

			///////////////////// END OPERATOR OVERLOADS /////////////////////
		};

		/**
		 * @brief A templated 3 component Vector.
		 * @tparam T The data type of the data being stored in the vector.
		 *
		 * This is for allowing more data to be passed more easily, or to store
		 * them tidily and simplify code usage.
		 */
		template <typename T> struct TemplateVector3
		{
			union {
				T x;
				T r;
			};

			union {
				T y;
				T g;
			};

			union {
				T z;
				T b;
			};

			TemplateVector3 () : x (T ()), y (T ()), z (T ()) {}
			TemplateVector3 (T x) : x (x), y (x), z (x) {}
			TemplateVector3 (T x, T y, T z) : x (x), y (y), z (z) {}
		};
	} // namespace math
} // namespace qz

/**
 * @brief Compares two vectors.
 * @param left The left hand side of the comparison.
 * @param right The right hand side of the comparison
 * @return True when both vectors are equivalent, otherwise false.
 */
inline bool operator== (const qz::math::Vector3& left,
                        const qz::math::Vector3& right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}

/**
 * @brief Compares two vectors.
 * @param left The left hand side of the comparison.
 * @param right The right hand side of the comparison
 * @return False when both vectors are equivalent, otherwise true.
 */
inline bool operator!= (const qz::math::Vector3& left,
                        const qz::math::Vector3& right)
{
	return left.x != right.x && left.y != right.y && left.z != right.z;
}
