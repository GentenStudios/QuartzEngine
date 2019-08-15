// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
// following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the
// following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
// following disclaimer in the documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
// products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.

#pragma once

#include <Quartz/Math/Math.hpp>

namespace ImGui
{
	/**
	 * @brief ImGui extension for a GUI representation of a Matrix4x4.
	 * @param label The label of the GUI element. Follows same rules as normal ImGui labels.
	 * @param mat4 Pointer to the Matrix4x4 that will be written to/read from.
	 *             Should not be null.
	 * @return Return if the GUI element has just been updated.
	 */
	bool InputMatrix4x4(const char* label, qz::Matrix4x4* mat4);

	/**
	 * @brief ImGui extension for a GUI representation of a Vector3
	 * @param label The label of the GUI element. Follows same rules as normal ImGui labels.
	 * @param vec3 Pointer to the Vector3 that will be written to/read from. Should not be null.
	 * @return Return if the GUI element has just been updated.
	 */
	bool InputVector3(const char* label, qz::Vector3* vec3);
	
	/**
	 * @brief ImGui extension for a GUI representaton of a Vector2
	 * @param label The label of the GUI element. Follows same rules as normal ImGui labels.
	 * @param vec2 Pointer to the Vector2 that will be written to/read from. Should not be null.
	 * @return Return if the GUI element has just been updated.
	 */
	bool InputVector2(const char* label, qz::Vector2* vec2);
	
	/**
	 * @brief ImGui extension for a slider GUI representation of a Matrix4x4.
	 * @param label The label of the GUI element. Follows same rules as normal ImGui labels.
	 * @param mat4 Pointer to the Matrix4x4 that will be written to/read from. Should not be null.
	 * @return Return if the GUI element has just been updated.
	 */
	bool SliderMatrix4x4(const char* label, qz::Matrix4x4* mat4);
	
	/**
	 * @brief ImGui extension for a slider GUI representation of a Vector3.
	 * @param label The label of the GUI element. Follows same rules as normal ImGui labels.
	 * @param vec3 Pointer to the Vector3 that will be written to/read from. Should not be null.
	 * @return Return if the GUI element has just been updated.
	 */
	bool SliderVector3(const char* label, qz::Vector3* vec3);

	/**
	 * @brief ImGui extension for a slider GUI representation of a Vector2
	 * @param label The label of the GUI element. Follows same rules as normal ImGui labels.
	 * @param vec2 Pointer to the Vector2 that will be written to/read from. Should not be null.
	 * @return Return if the GUI element has just been updated.
	 */
	bool SliderVector2(const char* label, qz::Vector2* vec2);

	/**
	 * @brief ImGui extension for a plotting a scalar float value on a graph.
	 * @param label The label of the GUI element. Follows same rules as normal ImGui labels.
	 * @param value Scalar float value to plot on the graph as it updates.
	 */
	void PlotVariable(const char* label, float value);
}
