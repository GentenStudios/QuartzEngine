#pragma once

#include <quartz/core/math/Matrix4x4.hpp>
#include <quartz/core/math/Vector3.hpp>
#include <quartz/core/math/Vector2.hpp>
#include <quartz/core/math/Ray.hpp>

namespace qz
{
	namespace math
	{
		typedef Matrix4x4				mat4;
		typedef Vector2					vec2;
		typedef Vector3					vec3;
		typedef	TemplateVector2<int>	vec2i;
		typedef	TemplateVector3<int>	vec3i;

		template <typename T>
		using tvec3 = TemplateVector3<T>;

		template <typename T>
		using tvec2 = TemplateVector2<T>;

		typedef Ray						ray;
	}
}
