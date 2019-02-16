#pragma once

#include <quartz/core/Core.hpp>

namespace qz
{
	namespace math
	{
		struct QZ_API Vector3
		{
			union { float x; float r; };
			union { float y; float g; };
			union { float z; float b; };

			Vector3()												: x(0), y(0), z(0) {}
			Vector3(const float x)									: x(x), y(x), z(x) {}
			Vector3(const float x, const float y, const float z)	: x(x), y(y), z(z) {}

			void			set			(const float scalar)	{ x = scalar; y = scalar; z = scalar; };
			void			floor();
			void			ceil();
			void			normalise();

			static Vector3	cross		(const Vector3& vec1, const Vector3& vec2);
			static Vector3	normalise	(const Vector3& vec1);
			static float	dotProduct	(const Vector3& vec1, const Vector3& vec2);

			void	operator+=	(const Vector3& other)			{ x += other.x; y += other.y; z += other.z; };
			void	operator-=	(const Vector3& other)			{ x += other.x; y += other.y; z += other.z; };
			void	operator+=	(const float& i)				{ x += i; y += i; z += i; }
			void	operator-=	(const float& i)				{ x -= i; y -= i; z -= i; }

			Vector3 operator+	(const Vector3& other)	const	{ return Vector3(x + other.x, y + other.y, z + other.z); }
			Vector3 operator-	(const Vector3& other)	const	{ return Vector3(x - other.x, y - other.y, z - other.z); }
			Vector3 operator+	(const float& i)		const	{ return Vector3(x + i, y + i, z + i); }
			Vector3 operator-	(const float& i)		const	{ return Vector3(x - i, y - i, z - i); }

			void	operator*=	(const Vector3& other)			{ x *= other.x; y *= other.y;	z *= other.z; };
			void	operator/=	(const Vector3& other)			{ x /= other.x; y /= other.y;	z /= other.z; };
			void	operator*=	(const float& scalar)			{ x *= scalar;	y *= scalar;	z *= scalar; }
			void	operator/=	(const float& scalar)			{ x /= scalar;	y /= scalar;	z /= scalar; }

			Vector3 operator*	(const Vector3& other)	const	{ return Vector3(x * other.x, y * other.y, z * other.z); }
			Vector3 operator/	(const Vector3& other)	const	{ return Vector3(x / other.x, y / other.y, z / other.z); }
			Vector3 operator*	(const float& scalar)	const	{ return Vector3(x * scalar, y * scalar, z * scalar); }
			Vector3 operator/	(const float& scalar)	const	{ return Vector3(x / scalar, y / scalar, z / scalar); }
		};

		template <typename T>
		struct QZ_API TemplateVector3
		{
			union { T x; T r; T a; };
			union {	T y; T g; T b; };
			union { T z; T b; T c; };

			TemplateVector3()				: x(T()),	y(T()), z(T())	{}
			TemplateVector3(T x)			: x(x),		y(x),	z(x)	{}
			TemplateVector3(T x, T y, T z)	: x(x),		y(y),	z(z)	{}		
		};
	}
}