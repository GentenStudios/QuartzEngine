#pragma once

#include <imgui.h>

#include "math/vector3.hpp"
#include "math/vector2.hpp"
#include "math/matrix4x4.hpp"

namespace ImGui {
	bool InputVector3(const char* name, phoenix::Vector3* vec3);
	bool InputVector2(const char* name, phoenix::Vector2* vec2);
	bool InputMatrix4x4(const char* name, phoenix::Matrix4x4* mat4);
}
