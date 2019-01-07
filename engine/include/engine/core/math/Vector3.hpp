/**
 * @file Vector3.hpp
 * @brief 3 Component Vector, for even more Mathematical FuN! HaS eVeN mOrE MaThS fUNctIoNs!
 */

#pragma once

namespace phx {

	/**
	 * @brief Represents a vector with 3 float components: x, y, z
	 */
	struct Vector3 {
		
		/// The X component of this vector
		union
		{
			float x;
			float r;
		};

		/// The Y component of this vector
		union
		{
			float y; 
			float g;
		};

		/// The Z component of this vector
		union
		{
			float z;
			float b;
		};

		/**
		 * @brief Constructs the Vector3 with the specified x, y and z components.
		 * @param x The initial 'x' value of this vector
		 * @param y The initial 'y' value of this vector
		 * @param z The initial 'z' value of this vector
		 */
		Vector3(const float& x, const float& y, const float& z);

		/**
		 * @brief Constructs the Vector3 initializing x, y and z to the same value.
		 * @param a The initial value for the x, y and z components
		 */
		Vector3(const float& a);

		/**
		 * @brief Default constructs the Vector3 initializing x, y and z with 0.0f
		 */
		Vector3();

		/**
		 * @brief Resets this vectors x, y and z component to the same specified value.
		 * @param a The new value for x, y and z
		 */
		void set(const float& a);

		/*
		 * @brief Floors each component of the vector.
		 */
		void floor();

		/**
		 * @brief Calculates the cross product of `a` and `b`
		 * @param a Left hand side of the calculation
		 * @param b Right hand side of the calculation
		 * @return The cross product of `a` and `b`
		 */
		static Vector3 cross(const Vector3& a, const Vector3& b);

		/**
		 * @brief Calculates the normal vector of vector `a`
		 * @param a The vector to normalize
		 * @return The normal vector of `a`
		 */
		static Vector3 normalize(const Vector3& a);

		/**
		 * @brief Calculates the dot product of vectors `a` and `b`
		 * @param a Left hand side of the calculation
		 * @param b Right hand side of the calculation
		 * @return The dot product of `a` and `b`
		 */
		static float   dot(const Vector3& a, const Vector3& b);

		/**
		 * @brief Adds another vector to this vector. Modifies this vector in place
		 * @param other The vector to add to this.
		 */
		void operator+=(const Vector3& other);

		/**
		 * @brief Subtracts another vector from this vector. Modifies this vector in place.
		 * @param other The vector to subtract from this vector.
		 */
		void operator-=(const Vector3& other);

	};

	typedef Vector3 Color3;

	/**
	 * @brief Adds two vectors - the equation is `p + q` where `p` and `q` are both 3 component vectors. Add's `left` to `right`
	 * @param left The left hand side of the addition
	 * @param right The right hand side of the addition
	 * @return The result of the addition of the 3 component vectors `left` and `right`
	 */
	Vector3 operator+(const Vector3& left, const Vector3& right);

	/**
	 * @brief Subtracts two vectors - the equation `p - q` where `p` and `q` are both 3 component vectors. Subtracts `right` from `left`
	 * @param left The left hand side of the subtraction
	 * @param right The right hand side of the subtraction
	 * @return The result of the subtraction of the two vectors `left - right`.
	 */
	Vector3 operator-(const Vector3& left, const Vector3& right);

	/**
	 * @brief Multiplies two vectors - the equation `p * q` where `p` and `q` are both 3 component vectors. Multiplies `right` and `left`.
	 * @param left The left hand side of the multiplication
	 * @param right The right hand side of the multiplication
	 * @return The product of `left` and `right`
	 */
	Vector3 operator*(const Vector3& left, const Vector3& right);

	/**
	 * @brief Divides two vectors - the equation `p / q` where `p` and `q` are both 3 component vectors. Divides `left` by `right`.
	 * @param left The left hand side of the division.
	 * @param right The right hand side of the division
	 * @return The quotient of `left` and `right`
	 */
	Vector3 operator/(const Vector3& left, const Vector3& right);

	/**
	 * @brief Compares two vectors.
	 * @param left The left hand side of the comparison.
	 * @param right The right hand side of the comparison
	 * @return True when both vectors are equivalent, otherwise false.
	 */
	bool operator==(const Vector3& left, const Vector3& right);

	/**
	 * @brief Compares two vectors.
	 * @param left The left hand side of the comparison.
	 * @param right The right hand side of the comparison
	 * @return False when both vectors are equivalent, otherwise true.
	 */
	bool operator!=(const Vector3& left, const Vector3& right);

}
