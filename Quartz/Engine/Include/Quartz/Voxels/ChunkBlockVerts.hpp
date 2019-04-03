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

#include <Quartz/Core/Math/Math.hpp>

const int ACTUAL_CUBE_SIZE = 2;
const int NUM_FACES_IN_CUBE = 6;
const int NUM_VERTS_IN_FACE = 6;

static const qz::Vector3 CUBE_VERTS[] = {
	// front
	qz::Vector3(-1.f, -1.f, -1.f),
	qz::Vector3(1.f, -1.f, -1.f),
	qz::Vector3(1.f,  1.f, -1.f),
	qz::Vector3(1.f,  1.f, -1.f),
	qz::Vector3(-1.f,  1.f, -1.f),
	qz::Vector3(-1.f, -1.f, -1.f),

	// back
	qz::Vector3(-1.f, -1.f, 1.f),
	qz::Vector3(1.f, -1.f, 1.f),
	qz::Vector3(1.f,  1.f, 1.f),
	qz::Vector3(1.f,  1.f, 1.f),
	qz::Vector3(-1.f,  1.f, 1.f),
	qz::Vector3(-1.f, -1.f, 1.f),

	// left
	qz::Vector3(-1.f,  1.f,  1.f),
	qz::Vector3(-1.f,  1.f, -1.f),
	qz::Vector3(-1.f, -1.f, -1.f),
	qz::Vector3(-1.f, -1.f, -1.f),
	qz::Vector3(-1.f, -1.f,  1.f),
	qz::Vector3(-1.f,  1.f,  1.f),

	// right
	qz::Vector3(1.f,  1.f,  1.f),
	qz::Vector3(1.f,  1.f, -1.f),
	qz::Vector3(1.f, -1.f, -1.f),
	qz::Vector3(1.f, -1.f, -1.f),
	qz::Vector3(1.f, -1.f,  1.f),
	qz::Vector3(1.f,  1.f,  1.f),

	// bottom
	qz::Vector3(-1.f, -1.f, -1.f),
	qz::Vector3(1.f, -1.f, -1.f),
	qz::Vector3(1.f, -1.f,  1.f),
	qz::Vector3(1.f, -1.f,  1.f),
	qz::Vector3(-1.f, -1.f,  1.f),
	qz::Vector3(-1.f, -1.f, -1.f),

	// top
	qz::Vector3(-1.f,  1.f, -1.f),
	qz::Vector3(1.f,  1.f, -1.f),
	qz::Vector3(1.f,  1.f,  1.f),
	qz::Vector3(1.f,  1.f,  1.f),
	qz::Vector3(-1.f,  1.f,  1.f),
	qz::Vector3(-1.f,  1.f, -1.f)
};

static const qz::Vector2 CUBE_UV[] = {
	// front north
	qz::Vector2(-0.f, 1.f),
	qz::Vector2(-1.f, 1.f),
	qz::Vector2(-1.f, 0.f),
	qz::Vector2(-1.f, 0.f),
	qz::Vector2(-0.f, 0.f),
	qz::Vector2(-0.f, 1.f),

	// back south
	qz::Vector2(0.f, 1.f),
	qz::Vector2(1.f, 1.f),
	qz::Vector2(1.f, 0.f),
	qz::Vector2(1.f, 0.f),
	qz::Vector2(0.f, 0.f),
	qz::Vector2(0.f, 1.f),

	// left west
	qz::Vector2(-0.f, 0.f),
	qz::Vector2(-1.f, 0.f),
	qz::Vector2(-1.f, 1.f),
	qz::Vector2(-1.f, 1.f),
	qz::Vector2(-0.f, 1.f),
	qz::Vector2(-0.f, 0.f),

	// right east
	qz::Vector2(0.f, 0.f),
	qz::Vector2(1.f, 0.f),
	qz::Vector2(1.f, 1.f),
	qz::Vector2(1.f, 1.f),
	qz::Vector2(0.f, 1.f),
	qz::Vector2(0.f, 0.f),

	// bottom
	qz::Vector2(0.f, 1.f),
	qz::Vector2(1.f, 1.f),
	qz::Vector2(1.f, 0.f),
	qz::Vector2(1.f, 0.f),
	qz::Vector2(0.f, 0.f),
	qz::Vector2(0.f, 1.f),

	// top
	qz::Vector2(0.f, -1.f),
	qz::Vector2(1.f, -1.f),
	qz::Vector2(1.f, -0.f),
	qz::Vector2(1.f, -0.f),
	qz::Vector2(0.f, -0.f),
	qz::Vector2(0.f, -1.f),
};
