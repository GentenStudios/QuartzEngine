// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#pragma once

#include <quartz/core/Core.hpp>

namespace qz
{
	namespace math
	{
		/**
		 * @brief A 2 Component Vector. Simplifies maths, and management of parameters.
		 */
		struct QZ_API Vector2
		{
			union { float x; float u; };
			union { float y; float v; };

			/**
			 * @brief Constructs a 2 Component Vector, each component is default initialized to 0.
			 */
			Vector2()								: x(0), y(0) {}

			/**
			 * @brief Constructs a 2 Component Vector.
			 * @param x The value the components should both be initialized to.
			 */
			Vector2(const float x)					: x(x), y(x) {}

			/**
			 * @brief Constructs a 2 Component Vector, each component is default initialized to 0.
			 * @param x The value the X component should be initialized to.
			 * @param y The value the Y component should be initialized to.
			 */
			Vector2(const float x, const float y)	: x(x), y(y) {}

			/**
			 * @brief Sets the components to a specific value.
			 * @param a The value to set the components to.
			 */
			void set(const float a) { x = a; y = a; };

			/**
			 * @brief Floors the components.
			 * 
			 * Flooring is (simply put) the process of rounding numbers down to the closest integer.
			 */
			void floor();

			/**
			 * @brief Ceils the components.
			 * 
			 * Ceiling is (simply put) the process of rounding numbers up to the closest integer.
			 */
			void ceil();

			///////////////////// OPERATOR OVERLOADS /////////////////////

			void	operator+=	(const Vector2& other)			{ x += other.x; y += other.y; };
			void	operator-=	(const Vector2& other)			{ x += other.x; y += other.y; };
			void	operator+=	(const float& i)				{ x += i; y += i; }
			void	operator-=	(const float& i)				{ x -= i; y -= i; }

			Vector2 operator+	(const Vector2& other)	const	{ return Vector2(x + other.x, y + other.y); }
			Vector2 operator-	(const Vector2& other)	const	{ return Vector2(x - other.x, y - other.y); }
			Vector2 operator+	(const float& i)		const	{ return Vector2(x + i, y + i); }
			Vector2 operator-	(const float& i)		const	{ return Vector2(x - i, y - i); }

			void	operator*=	(const Vector2& other)			{ x *= other.x; y *= other.y; };
			void	operator/=	(const Vector2& other)			{ x /= other.x; y /= other.y; };
			void	operator*=	(const float& scalar)			{ x *= scalar; y *= scalar; }
			void	operator/=	(const float& scalar)			{ x /= scalar; y /= scalar; }

			Vector2 operator*	(const Vector2& other)	const	{ return Vector2(x * other.x, y * other.y); }
			Vector2 operator/	(const Vector2& other)	const	{ return Vector2(x / other.x, y / other.y); }
			Vector2 operator*	(const float& scalar)	const	{ return Vector2(x * scalar, y * scalar); }
			Vector2 operator/	(const float& scalar)	const	{ return Vector2(x / scalar, y / scalar); }

			///////////////////// END OPERATOR OVERLOADS /////////////////////
		};

		/**
		 * @brief A templated 2 component Vector.
		 * @tparam T The data type of the data being stored in the vector.
		 * 
		 * This is for allowing more data to be passed more easily, or to store them tidily and simplify code usage.
		 */
		template <typename T>
		struct QZ_API TemplateVector2
		{
			union { T x; T u; };
			union {	T y; T v; };

			TemplateVector2()			: x(T()),	y(T())	{}
			TemplateVector2(T x)		: x(x),		y(x)	{}
			TemplateVector2(T x, T y)	: x(x),		y(y)	{}		
		};
	}
}
