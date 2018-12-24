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
	for (size_t x = 0; x < blockArray.size(); x++)
	{
		for (size_t y = 0; y < blockArray[x].size(); y++)
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

			for (size_t z = 0; z < blockArray[x][y].size(); z++)
			{
				int x1 = x,
					z1 = z;

				float noise = at(
					((static_cast<float>(x1) + chunkPos.x) * 8) / 512.f,
					((static_cast<float>(z1) + chunkPos.z) * 8) / 512.f
				) + 1.0f;

				int newY = static_cast<int>(noise * 8) % 16;

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
	return dx * std::get<0>(m_gradient[iy % PERLIN_YMAX][ix % PERLIN_XMAX]) +
		dy * std::get<1>(m_gradient[iy % PERLIN_YMAX][ix % PERLIN_XMAX]);
}

float PerlinNoise::at(float x, float z)
{
	if (x < 0)
		x = fabs(x);

	if (z < 0)
		z = fabs(z);

	int x0 = static_cast<int>(x);
	int x1 = x0 + 1;
	int z0 = static_cast<int>(z);
	int z1 = z0 + 1;

	float sx = x - static_cast<float>(x0);
	float sz = z - static_cast<float>(z0);

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

float PerlinNoise::atOctave(float x, float z, float octaves, float persitance)
{
	float tot = 0;
	float f = 1;
	float a = 1;
	float maxValue = 0;
	for (int i = 0; i < octaves; ++i)
	{
		tot += at(x * f, z * f) * a;
		maxValue += a;
		a *= persitance;
		f *= 2;
	}
	return tot / maxValue;
}
