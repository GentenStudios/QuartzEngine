#include "engine/imgui.hpp"

bool ImGui::InputVector3(const char * name, phoenix::Vector3 * vec3)
{
	return ImGui::InputFloat3(name, &(vec3->x));
}

bool ImGui::InputVector2(const char * name, phoenix::Vector2 * vec2)
{
	return ImGui::InputFloat3(name, &(vec2->x));
}

bool ImGui::InputMatrix4x4(const char * name, phoenix::Matrix4x4 * mat4)
{
	int id = ImGui::GetID(name);
	float* ptr = &(mat4->elements[0]);

	bool r1 = ImGui::InputFloat4(name, ptr);

	ImGui::PushID(id + 1);
	bool r2 = ImGui::InputFloat4("", ptr + 4);
	ImGui::PopID();

	ImGui::PushID(id + 2);
	bool r3 = ImGui::InputFloat4("", ptr + 8);
	ImGui::PopID();

	ImGui::PushID(id + 3);
	bool r4 = ImGui::InputFloat4("", ptr + 12);
	ImGui::PopID();

	return r1 || r2 || r3 || r4;
}
