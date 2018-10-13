#include "engine/math/matrix4x4.hpp"

#include <cstring>

using namespace phoenix;

#define INDEX2D(x, y) (x + y * 4)

Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < 4 * 4; ++i) elements[i] = 0.f;

	elements[INDEX2D(0, 0)] = 1.f;
	elements[INDEX2D(1, 1)] = 1.f;
	elements[INDEX2D(2, 2)] = 1.f;
	elements[INDEX2D(3, 3)] = 1.f;
}