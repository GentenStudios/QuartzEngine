#pragma once

#include <engine/core/math/Vector3.hpp>
#include <engine/voxels/Block.hpp>

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
			float at(phx::Vector3 pos) const;
			float atOctave(phx::Vector3 pos, int octaves, float persitance) const;

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