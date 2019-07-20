// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVidED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCidENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <Quartz/Graphics/ImGuiExtensions.hpp>
#include <imgui/imgui.h>
#include <map>
#include <vector>

bool ImGui::InputMatrix4x4 (const char* label, qz::Matrix4x4* mat4)
{
	ImGui::Text ("%s", label);

	ImGui::PushID (label);

	ImGui::PushID (0);
	bool row0 = ImGui::InputFloat4 ("", mat4->elements);
	ImGui::PopID ();

	ImGui::PushID (1);
	bool row1 = ImGui::InputFloat4 ("", mat4->elements + 4);
	ImGui::PopID ();

	ImGui::PushID (2);
	bool row2 = ImGui::InputFloat4 ("", mat4->elements + 8);
	ImGui::PopID ();

	ImGui::PushID (3);
	bool row3 = ImGui::InputFloat4 ("", mat4->elements + 12);
	ImGui::PopID ();

	ImGui::PopID ();

	return row0 || row1 || row2 || row3;
}

bool ImGui::InputVector3 (const char* label, qz::Vector3* vec3)
{
	float* dat = &(vec3->x);
	return ImGui::InputFloat3 (label, dat);
}

bool ImGui::InputVector2 (const char* label, qz::Vector2* vec2)
{
	float* dat = &(vec2->x);
	return ImGui::InputFloat2 (label, dat);
}

struct PlotVarData
{
	ImGuiID            id;
	std::vector<float> data;
	int                dataInsertIdx;
	int                lastFrame;

	PlotVarData () : id (0), dataInsertIdx (0), lastFrame (-1) {}
};

static std::map<ImGuiID, PlotVarData> g_PlotVarsMap;

void ImGui::PlotVariable (const char* label, float value)
{
	const int bufferSize = 120;

	ImGui::PushID (label);
	const ImGuiID id = ImGui::GetID ("");

	PlotVarData& pvd = g_PlotVarsMap[id];

	if (pvd.data.capacity () != bufferSize)
	{
		pvd.data.resize (bufferSize);
		memset (&pvd.data[0], 0, sizeof (float) * bufferSize);
		pvd.dataInsertIdx = 0;
		pvd.lastFrame     = -1;
	}

	if (pvd.dataInsertIdx == bufferSize)
		pvd.dataInsertIdx = 0;

	const int displayIndex = pvd.dataInsertIdx;

	if (value != FLT_MAX)
		pvd.data[pvd.dataInsertIdx++] = value;

	const int currentFrame = ImGui::GetFrameCount ();
	if (pvd.lastFrame != currentFrame)
	{
		ImGui::PlotLines ("##plot", &pvd.data[0], bufferSize, pvd.dataInsertIdx,
		                  nullptr, FLT_MIN, FLT_MAX, ImVec2 (0, 40));
		ImGui::SameLine ();
		ImGui::Text ("%s\n%-3.4f", label, pvd.data[displayIndex]);
		pvd.lastFrame = currentFrame;
	}

	ImGui::PopID ();
}
