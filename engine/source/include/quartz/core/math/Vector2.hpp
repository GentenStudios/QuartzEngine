#pragma once

#include <quartz/core/Core.hpp>

namespace qz
{
	namespace math
	{
		struct QZ_API Vector2
		{
			union { float x; float u; };
			union { float y; float v; };

			Vector2()								: x(0), y(0) {}
			Vector2(const float x)					: x(x), y(x) {}
			Vector2(const float x, const float y)	: x(x), y(y) {}

			void set(const float a) { x = a; y = a; };
			void floor();
			void ceil();

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
		};

		template <typename T>
		struct QZ_API TemplateVector2
		{
			union { T x; T u; T a; };
			union {	T y; T v; T b; };

			TemplateVector2()			: x(T()),	y(T())	{}
			TemplateVector2(T x)		: x(x),		y(x)	{}
			TemplateVector2(T x, T y)	: x(x),		y(y)	{}		
		};
	}
}