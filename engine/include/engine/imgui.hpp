#pragma once

#include <imgui.h>

#include "math/vector3.hpp"
#include "math/vector2.hpp"
#include "math/matrix4x4.hpp"

namespace ImGui {
	/**
	 * @brief Creates an ImGui widget for editing a phoenix::Vector3.
	 * @param name The unique name (is treated as an ID) for this widget
	 * @param vec3 A pointer to the phoenix::Vector3 object that this widget is connected to.
	 * @return Return's true if the Vector3 has been edited through the widget.
	 */
	bool InputVector3(const char* name, phoenix::Vector3* vec3);

	/**
	* @brief Creates an ImGui widget for editing a phoenix::Vector2.
	* @param name The unique name (is treated as an ID) for this widget
	* @param vec2 A pointer to the phoenix::Vector2 object that this widget is connected to.
	* @return Return's true if the Vector2 has been edited through the widget.
	*/
	bool InputVector2(const char* name, phoenix::Vector2* vec2);

	/**
	* @brief Creates an ImGui widget for editing a phoenix::Matrix4x4.
	* @param name The unique name (is treated as an ID) for this widget
	* @param mat4 A pointer to the phoenix::Matrix4x4 object that this widget is connected to.
	* @return Return's true if the Matrix4x4 has been edited through the widget.
	*/
	bool InputMatrix4x4(const char* name, phoenix::Matrix4x4* mat4);
}
