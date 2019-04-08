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

#include <Quartz/Core/QuartzPCH.hpp>
#include <Quartz/Voxels/Terrain/PerlinNoise.hpp>
#include <Quartz/Core/Utilities/FileIO.hpp>
#include <Quartz/Voxels/Chunk.hpp>

#include <algorithm>
#include <random>
#include <numeric>
#include <functional>

using namespace qz::voxels;

static int s_permutation[] = {
	151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
	8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203,
	117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74,
	165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220,
	105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
	187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186,
	3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
	47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221,
	153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185,
	112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51,
	145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
	50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215,
	61, 156, 180 };

PerlinNoise::PerlinNoise()
{
	for (int i : s_permutation)
	{
		m_p.push_back(i);
	}

	m_p.insert(m_p.end(), m_p.begin(), m_p.end());

	// need a better way to load the script
	m_lua.Register("loadModel", [&](std::string filename){
		this->m_lua.RunString(qz::utils::FileIO::readAllFile("assets/scripts/" + filename).c_str());
	});
	m_lua.RunString(qz::utils::FileIO::readAllFile("assets/scripts/PerlinNoise.lua").c_str());
}

PerlinNoise::PerlinNoise(unsigned int seed)
{
	m_p.resize(256);

	std::iota(m_p.begin(), m_p.end(), 0);

	std::default_random_engine engine(seed);
	std::shuffle(m_p.begin(), m_p.end(), engine);
	m_p.insert(m_p.end(), m_p.begin(), m_p.end());

	// need a better way to load the script
	m_lua.Register("loadModel", [&](std::string filename){
		this->m_lua.RunString(qz::utils::FileIO::readAllFile("assets/scripts/" + filename).c_str());
	});
	m_lua.RunString(qz::utils::FileIO::readAllFile("assets/scripts/PerlinNoise.lua").c_str());
}

void PerlinNoise::generateFor(std::vector<BlockInstance>& blockArray, qz::Vector3 chunkPos)
{
	const float smoothing = m_lua.Call<float>("getSmoothingFactor", chunkPos.x, chunkPos.y, chunkPos.z);

	for (int x = 0; x < Chunk::CHUNK_WIDTH; ++x)
	{
		for (int y = 0; y < Chunk::CHUNK_HEIGHT; ++y)
		{
			if (chunkPos.y + y >= 16)
			{
				for (int z = 0; z < Chunk::CHUNK_DEPTH; ++z)
				{
					blockArray[Chunk::getVectorIndex(x, y, z)] = BlockInstance("core:air");
				}
				continue;
			}

			if (chunkPos.y + y < 0)
			{
				for (int z = 0; z < Chunk::CHUNK_DEPTH; ++z)
				{
					blockArray[Chunk::getVectorIndex(x, y, z)] = BlockInstance("core:air");
				}
				continue;
			}

			for (int z = 0; z < Chunk::CHUNK_DEPTH; ++z)
			{
				// Block Position with the smoothing factor applied to it.
				// The division by 'smoothing' helps "decide" how smooth the generated terrain will be.
				const qz::Vector3 blockPosWithSmoothingApplied = { 
					(static_cast<float>(x) + chunkPos.x) / smoothing,
					(static_cast<float>(z) + chunkPos.z) / smoothing,
					(static_cast<float>(0) + chunkPos.y) / smoothing
				};
				const float noise = at(blockPosWithSmoothingApplied);

				const int newY = static_cast<int>(noise * Chunk::CHUNK_HEIGHT) % Chunk::CHUNK_HEIGHT;

				blockArray[Chunk::getVectorIndex(x, newY, z)] = BlockInstance("core:grass");

				for (int y2 = 0; y2 < newY; ++y2)
				{
					blockArray[Chunk::getVectorIndex(x, y2, z)] = BlockInstance("core:dirt");
				}
			}
		}
	}
}

float PerlinNoise::fade(float t) const
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::grad(int hash, float x, float y, float z) const
{
	int h = hash & 15;

	float u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float PerlinNoise::lerp(float t, float a, float b) const
{
	return a + t * (b - a);
}

float PerlinNoise::at(qz::Vector3 pos) const
{
	int X = static_cast<int>(std::floor(pos.x)) & 255;
	int Y = static_cast<int>(std::floor(pos.y)) & 255;
	int Z = static_cast<int>(std::floor(pos.z)) & 255;

	pos.x -= std::floor(pos.x);
	pos.y -= std::floor(pos.y);
	pos.z -= std::floor(pos.z);

	float u = fade(pos.x);
	float v = fade(pos.y);
	float w = fade(pos.z);

	int A = m_p[X] + Y;
	int AA = m_p[A] + Z;
	int AB = m_p[A + 1] + Z;
	int B = m_p[X + 1] + Y;
	int BA = m_p[B] + Z;
	int BB = m_p[B + 1] + Z;

	float res = lerp(
		w, lerp(v, lerp(u, grad(m_p[AA], pos.x, pos.y, pos.z), grad(m_p[BA], pos.x - 1, pos.y, pos.z)),
				lerp(u, grad(m_p[AB], pos.x, pos.y - 1, pos.z), grad(m_p[BB], pos.x - 1, pos.y - 1, pos.z))), lerp(
			v, lerp(u, grad(m_p[AA + 1], pos.x, pos.y, pos.z - 1), grad(m_p[BA + 1], pos.x - 1, pos.y, pos.z - 1)),
			lerp(u, grad(m_p[AB + 1], pos.x, pos.y - 1, pos.z - 1),
				grad(m_p[BB + 1], pos.x - 1, pos.y - 1, pos.z - 1))));

	return (res + 1.f) / 2.f;
}

float PerlinNoise::atOctave(qz::Vector3 pos, int octaves, float persitance) const
{
	float tot = 0;
	float f = 1;
	float a = 1;
	float maxValue = 0;
	for (int i = 0; i < octaves; ++i)
	{
		tot += at(qz::Vector3(pos.x * f, pos.y * f, pos.z * f)) * a;
		maxValue += a;
		a *= persitance;
		f *= 2;
	}
	return tot / maxValue;
}

