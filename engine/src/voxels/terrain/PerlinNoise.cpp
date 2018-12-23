#include <engine/voxels/terrain/PerlinNoise.hpp>

#include <algorithm>
#include <ctime>

using namespace phx::voxels;

PerlinNoise::PerlinNoise()
{
	createDistribution(static_cast<unsigned int>(time(0)));
}

PerlinNoise::PerlinNoise(unsigned int seed)
{
	createDistribution(seed);
}

void PerlinNoise::createDistribution(unsigned int seed)
{
	srand(seed);

	// initialize m_gradient with random values
	for (auto& y : m_gradient)
	{
		for (auto& x : y)
			x = std::make_tuple(getRand(), getRand());
	}
}

void PerlinNoise::generateFor(std::vector<std::vector<std::vector<BlockInstance>>>& blockArray, phx::Vector3 chunkPos)
{
	for (int x = 0; x < blockArray.size(); x++)
	{
		for (int y = 0; y < blockArray[x].size(); y++)
		{
			if (chunkPos.y + y >= 16)
			{
				for (auto& z : blockArray[x][y])
				{
					z = BlockInstance("core:air");
				}
				continue;
			}

			if (chunkPos.y + y < 0)
			{
				for (auto& z : blockArray[x][y])
				{
					z = BlockInstance("core:dirt");
				}
				continue;
			}

			for (int z = 0; z < blockArray[x][y].size(); z++)
			{
				int x1 = x,
					z1 = z;

				float noise = at(
					((static_cast<float>(x1) + chunkPos.x) * 16) / 256.f,
					((static_cast<float>(z1) + chunkPos.z) * 16) / 256.f
				) + 1.0f;

				int newY = static_cast<int>(noise * 16.f);
				newY = std::max(0, std::min(newY, 15));

				blockArray[x][newY][z] = BlockInstance("core:grass");

				for (int y = 0; y < newY; y++)
				{
					blockArray[x][y][z] = BlockInstance("core:dirt");
				}

				//LDEBUG("Let's See: ", newY);
			}
		}
	}
}

float PerlinNoise::dotGridGradient(int ix, int iy, float x, float y)
{
	float dx = x - static_cast<float>(ix);
	float dy = y - static_cast<float>(iy);

	// be sure to stay in range
	return dx * std::get<0>(m_gradient[abs(iy) % PERLIN_YMAX][abs(ix) % PERLIN_XMAX]) +
		dy * std::get<1>(m_gradient[abs(iy) % PERLIN_YMAX][abs(ix) % PERLIN_XMAX]);
}

float PerlinNoise::at(float x, float z)
{
	// grid cell coords
	int x0 = static_cast<int>(x), x1 = x0 + 1,
		z0 = static_cast<int>(z), z1 = z0 + 1;

	// interpolation weights
	// (could use higher order polynomial/s-curve)
	float sx = x - static_cast<float>(x0),
		sz = z - static_cast<float>(z0);

	// interpolation between grid point gradients
	float n0{}, n1{}, ix0{}, ix1{};

	n0 = dotGridGradient(x0, z0, x, z);
	n1 = dotGridGradient(x1, z0, x, z);
	ix0 = lerp(n0, n1, sx);
	n0 = dotGridGradient(x0, z1, x, z);
	n1 = dotGridGradient(x1, z1, x, z);
	ix1 = lerp(n0, n1, sx);

	return lerp(ix0, ix1, sz);
}