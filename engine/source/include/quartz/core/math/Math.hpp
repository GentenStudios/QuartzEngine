#pragma once

#include <quartz/core/math/MathUtils.hpp>
#include <quartz/core/math/Matrix4x4.hpp>
#include <quartz/core/math/Vector3.hpp>
#include <quartz/core/math/Vector2.hpp>
#include <quartz/core/math/Ray.hpp>

namespace qz
{
	typedef math::Matrix4x4				Matrix4x4;

	typedef math::Vector2				Vector2;
	typedef math::Vector3				Vector3;
	typedef math::TemplateVector2<int>	Vector2i;
	typedef math::TemplateVector3<int>	Vector3i;

	template <typename T> using TVector2 = math::TemplateVector2<T>;
	template <typename T> using TVector3 = math::TemplateVector3<T>;
}
