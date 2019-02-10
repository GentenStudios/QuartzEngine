#pragma once

#include <quartz/core/math/Vector3.hpp>
#include <quartz/voxels/Block.hpp>

namespace qz
{
	namespace voxels
	{
		class PerlinNoise
		{
		public:
			PerlinNoise();
			PerlinNoise(unsigned int seed);
			~PerlinNoise() = default;

			void generateFor(std::vector<BlockInstance>& blockArray, qz::Vector3 chunkPos, int chunkSize);
			float at(qz::Vector3 pos) const;
			float atOctave(qz::Vector3 pos, int octaves, float persitance) const;

		private:
			std::vector<int> m_p;
			int m_chunkSize;

			float fade(float t) const;
			float grad(int hash, float x, float y, float z) const;
			float lerp(float t, float a, float b) const;

			std::size_t getVectorIndex(const int x, const int y, const int z) const
			{
				return x + m_chunkSize * (y + m_chunkSize * z);
			}
		};
	}
}