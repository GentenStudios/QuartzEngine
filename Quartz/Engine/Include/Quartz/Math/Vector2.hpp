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
#include <ostream>

namespace qz
{
	namespace math
	{
		namespace detail
		{
			template <typename T>
			class Vector2
			{
			public:
				using ValueType           = T;
				using ValueReference      = T&;
				using ConstValueReference = const T&;

				static constexpr int SIZE = 2;
				static constexpr int size() { return SIZE; }

				union {
					T data[SIZE];
					struct
					{
						T x;
						T y;
					};
					struct
					{
						T u;
						T v;
					};
				};

				constexpr Vector2() : x(), y() {}

				template <typename X>
				constexpr explicit Vector2(X val)
				    : x(static_cast<T>(val)), y(static_cast<T>(val))
				{
				}

				template <typename X, typename Y>
				constexpr Vector2(X x, Y y)
				    : x(static_cast<T>(x)), y(static_cast<T>(y))
				{
				}

				template <typename X>
				constexpr Vector2(const Vector2<X>& rhs)
				    : x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y))
				{
				}

				template <typename X>
				Vector2& operator=(const Vector2<X>& rhs)
				{
					x = static_cast<T>(rhs.x);
					y = static_cast<T>(rhs.y);
					return *this;
				}

				template <typename NewType>
				explicit constexpr operator Vector2<NewType>() const
				{
					Vector2<NewType> vec;

					vec.x = static_cast<NewType>(x);
					vec.y = static_cast<NewType>(y);

					return vec;
				}

				void floor()
				{
					std::floor(x);
					std::floor(y);
				}
				void ceil()
				{
					std::ceil(x);
					std::ceil(y);
				}

				bool operator==(const Vector2& rhs) const
				{
					return (x == rhs.x && y == rhs.y);
				}
				bool operator!=(const Vector2& rhs) const
				{
					return (x != rhs.x && y != rhs.y);
				}
				bool operator>(const Vector2& rhs) const
				{
					return (x > rhs.x && y > rhs.y);
				}
				bool operator<(const Vector2& rhs) const
				{
					return (x < rhs.x && y < rhs.y);
				}
				bool operator>=(const Vector2& rhs) const
				{
					return (x >= rhs.x && y >= rhs.y);
				}
				bool operator<=(const Vector2& rhs) const
				{
					return (x <= rhs.x && y <= rhs.y);
				}

				Vector2 operator+(const Vector2& rhs)
				{
					return Vector2(x + rhs.x, y + rhs.y);
				}
				Vector2 operator-(const Vector2& rhs)
				{
					return Vector2(x - rhs.x, y - rhs.y);
				}
				Vector2 operator*(const Vector2& rhs)
				{
					return Vector2(x * rhs.x, y * rhs.y);
				}
				Vector2 operator/(const Vector2& rhs)
				{
					return Vector2(x / rhs.x, y / rhs.y);
				}
				void operator+=(const Vector2& rhs) { x += rhs.x, y += rhs.y; }
				void operator-=(const Vector2& rhs) { x -= rhs.x, y -= rhs.y; }
				void operator*=(const Vector2& rhs) { x *= rhs.x, y *= rhs.y; }
				void operator/=(const Vector2& rhs) { x /= rhs.x, y /= rhs.y; }

				Vector2 operator+(const T& rhs)
				{
					return Vector2(x + rhs, y + rhs);
				}
				Vector2 operator-(const T& rhs)
				{
					return Vector2(x - rhs, y - rhs);
				}
				Vector2 operator*(const T& rhs)
				{
					return Vector2(x * rhs, y * rhs);
				}
				Vector2 operator/(const T& rhs)
				{
					return Vector2(x / rhs, y / rhs);
				}
				void operator+=(const T& rhs) { x += rhs, y += rhs; }
				void operator-=(const T& rhs) { x -= rhs, y -= rhs; }
				void operator*=(const T& rhs) { x *= rhs, y *= rhs; }
				void operator/=(const T& rhs) { x /= rhs, y /= rhs; }

				Vector2& operator++()
				{
					++x;
					++y;
					return *this;
				}
				Vector2 operator++(int)
				{
					Vector2 result(*this);
					++(*this);
					return result;
				}
				Vector2& operator--()
				{
					--x;
					--y;
					return *this;
				}
				Vector2 operator--(int)
				{
					Vector2 result(*this);
					--(*this);
					return result;
				}

				friend std::ostream& operator<<(std::ostream&  os,
				                                const Vector2& vec)
				{
					os << "(" << vec.x << ", " << vec.y << ")";
					return os;
				}
			};
		} // namespace detail
	} // namespace math
} // namespace qz

template <typename T>
qz::math::detail::Vector2<T> operator-(
    const qz::math::detail::Vector2<T>& left,
    const qz::math::detail::Vector2<T>& right)
{
	return {left.x - right.x, left.y - right.y};
}

template <typename T>
qz::math::detail::Vector2<T> operator+(
    const qz::math::detail::Vector2<T>& left,
    const qz::math::detail::Vector2<T>& right)
{
	return {left.x + right.x, left.y + right.y};
}

template <typename T>
qz::math::detail::Vector2<T> operator*(
    const qz::math::detail::Vector2<T>& left,
    const qz::math::detail::Vector2<T>& right)
{
	return {left.x * right.x, left.y * right.y};
}

template <typename T>
qz::math::detail::Vector2<T> operator/(
    const qz::math::detail::Vector2<T>& left,
    const qz::math::detail::Vector2<T>& right)
{
	return {left.x / right.x, left.y / right.y};
}

