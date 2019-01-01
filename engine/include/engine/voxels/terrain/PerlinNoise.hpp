#pragma once

#include <engine/core/Core.hpp>
#include <engine/core/math/Vector3.hpp>

#include <engine/voxels/Block.hpp>

#include <array>

#define PERLIN_XMAX 256
#define PERLIN_YMAX 256

namespace phx
{
	namespace voxels
	{

		class PerlinNoise
		{
		public:
			PerlinNoise();
			PerlinNoise(unsigned int seed);
			~PerlinNoise() = default;

			void generateFor(std::vector<BlockInstance>& blockArray, phx::Vector3 chunkPos, int chunkSize);
			float at(phx::Vector3 pos);
			float atOctave(phx::Vector3 pos, int octaves, float persitance);

		private:
			std::vector<int> m_p;
			int m_repeat;
			int m_chunkSize;

			float fade(float t);
			float grad(int hash, float x, float y, float z);
			float lerp(float t, float a, float b);

			std::size_t getVectorIndex(int x, int y, int z) const
			{
				return x + m_chunkSize * (y + m_chunkSize * z);
			}
		};

	}
}