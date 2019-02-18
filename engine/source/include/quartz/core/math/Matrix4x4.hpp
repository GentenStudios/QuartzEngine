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
			Matrix4x4::Matrix4x4(
				float m00, float m10, float m20, float m30,
				float m01, float m11, float m21, float m31,
				float m02, float m12, float m22, float m32,
				float m03, float m13, float m23, float m33
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