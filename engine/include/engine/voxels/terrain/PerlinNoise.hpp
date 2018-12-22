#pragma once

#include <engine/core/Core.hpp>
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
			PerlinNoise(const PerlinNoise&) = default;
			~PerlinNoise();

			void init();
			void generateFor(std::vector<std::vector<std::vector<BlockInstance>>>& blockArray, phx::Vector3 chunkPos);

			float perlin(phx::Vector3 pos);

		private:
			float fade(float t);
			int inc(int num);
			float grad(int hash, float x, float y, float z);
			float lerp(float a, float b, float x);

			int m_p[512];
			int m_repeat;
		};

	}
}