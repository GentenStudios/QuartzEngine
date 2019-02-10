#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/math/Vector3.hpp>

namespace qz
{
	namespace math
	{

		struct QZ_API Matrix4x4
		{
			float elements[16];

			Matrix4x4();
			Matrix4x4(
				float e0,	float e4,	float e8,	float e12, 
				float e1,	float e5,	float e9,	float e13,
				float e2,	float e6,	float e10,	float e14,
				float e3,	float e7,	float e11,	float e15
				);

			~Matrix4x4() = default;

			static Matrix4x4 perspective(
				const float& aspectRatio,
				const float& fieldOfView,
				const float& farPlane,
				const float& nearPlane
			);

			static Matrix4x4 ortho(float left, 
				float right, 
				float top, 
				float bottom, 
				float farPlane, 
				float nearPlane
			);

			static Matrix4x4 lookAt(
				const Vector3& eyePos,
				const Vector3& centre,
				const Vector3& up
			);

			void operator*=(const Matrix4x4& other);
			Matrix4x4 operator*(const Matrix4x4& other);

			void operator*=(const float& other);
			Matrix4x4 operator*(const float& other);

			Vector3 operator*(const Vector3& other);
		};
	};
}