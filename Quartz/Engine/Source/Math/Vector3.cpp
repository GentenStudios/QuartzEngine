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
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <Quartz/Math/Vector3.hpp>
#include <Quartz/QuartzPCH.hpp>

using namespace qz::math;

void Vector3::floor()
{
	x = std::floor(x);
	y = std::floor(y);
	z = std::floor(z);
}

void Vector3::ceil()
{
	x = std::ceil(x);
	y = std::ceil(y);
	z = std::ceil(z);
}

void Vector3::normalize()
{
	const float len = std::sqrt(dotProduct({x, y, z}, {x, y, z}));

	x /= len;
	y /= len;
	z /= len;
}

Vector3 Vector3::cross(const Vector3& vec1, const Vector3& vec2)
{
	return {vec1.y * vec2.z - vec1.z * vec2.y,
	        vec1.z * vec2.x - vec1.x * vec2.z,
	        vec1.x * vec2.y - vec1.y * vec2.x};
}

Vector3 Vector3::normalize(const Vector3& vec1)
{
	const float len = std::sqrt(dotProduct(vec1, vec1));

	return {vec1.x / len, vec1.y / len, vec1.z / len};
}

float Vector3::dotProduct(const Vector3& vec1, const Vector3& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}
