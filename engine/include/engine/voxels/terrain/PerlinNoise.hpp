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

			void generateFor(std::vector<std::vector<std::vector<BlockInstance>>>& blockArray, phx::Vector3 chunkPos);
			float at(float x, float z);
			float atOctave(float x, float z, float octaves, float persistance);

		private:
			std::array<
				std::array<
				std::tuple<float, float>, PERLIN_XMAX
				>, PERLIN_YMAX
			> m_gradient;

			// w should be in range [0.0f, 1.0f]
			inline float lerp(float a0, float a1, float w)
			{
				return (1.0f - w) * a0 + w * a1;
			}

			inline float getRand()
			{
				return -1.0f + 2.0f * ((float)rand()) / RAND_MAX;
			}

			float dotGridGradient(int ix, int iy, float x, float y);

			void createDistribution(unsigned int seed);
		};

	}
}