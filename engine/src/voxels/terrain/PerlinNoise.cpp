#include <engine/voxels/terrain/PerlinNoise.hpp>

#include <algorithm>
#include <ctime>

using namespace phx::voxels;

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
	for (int i = 0; i < 512; ++i)
		m_p.push_back(s_permutation[i % 256]);
}

PerlinNoise::PerlinNoise(unsigned int seed)
{
	std::srand(seed);

	for (int i = 0; i < 256; ++i)
	{
		m_p.push_back(i);
		m_p.push_back(i);
	}

	std::random_shuffle(m_p.begin(), m_p.end());
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
					{
					((static_cast<float>(x1) + chunkPos.x) * 2) / 64.f,
					((static_cast<float>(z1) + chunkPos.z) * 2) / 64.f,
					((static_cast<float>(0)  + chunkPos.y) * 2) / 64.f
					}
				);

				int newY = static_cast<int>(noise * 16) % 16;

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

float PerlinNoise::fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

int PerlinNoise::inc(int num)
{
	num++;
	if (m_repeat > 0)
		num %= m_repeat;
	return num;
}

float PerlinNoise::grad(int hash, float x, float y, float z)
{
	switch (hash & 0xF)
	{
	case 0x0:
		return x + y;
	case 0x1:
		return -x + y;
	case 0x2:
		return x - y;
	case 0x3:
		return -x - y;
	case 0x4:
		return x + z;
	case 0x5:
		return -x + z;
	case 0x6:
		return x - z;
	case 0x7:
		return -x - z;
	case 0x8:
		return y + z;
	case 0x9:
		return -y + z;
	case 0xA:
		return y - z;
	case 0xB:
		return -y - z;
	case 0xC:
		return y + x;
	case 0xD:
		return -y + z;
	case 0xE:
		return y - x;
	case 0xF:
		return -y - z;
	default:
		return 0;
	}
}

float PerlinNoise::lerp(float a, float b, float x)
{
	return a + x * (b - a);
}

float PerlinNoise::at(phx::Vector3 pos)
{
	if (m_repeat > 0)
	{
		pos.x = static_cast<float>((int)pos.x % m_repeat);
		pos.y = static_cast<float>((int)pos.y % m_repeat);
		pos.z = static_cast<float>((int)pos.z % m_repeat);
	}

	phx::Vector3 posi(
		static_cast<float>(static_cast<int>(pos.x) & 255),
		static_cast<float>(static_cast<int>(pos.y) & 255),
		static_cast<float>(static_cast<int>(pos.z) & 255)
	);

	phx::Vector3 posf(
		pos.x - static_cast<int>(pos.x),
		pos.y - static_cast<int>(pos.y),
		pos.z - static_cast<int>(pos.z));

	float u = fade(posf.x);
	float v = fade(posf.y);
	float w = fade(posf.z);

	int xi = posi.x;
	int yi = posi.y;
	int zi = posi.z;

	float xf = posf.x;
	float yf = posf.y;
	float zf = posf.z;

	int aaa = m_p[m_p[m_p[xi] + yi] + zi];
	int aba = m_p[m_p[m_p[xi] + inc(yi)] + zi];
	int aab = m_p[m_p[m_p[xi] + yi] + inc(zi)];
	int abb = m_p[m_p[m_p[xi] + inc(yi)] + inc(zi)];
	int baa = m_p[m_p[m_p[inc(xi)] + yi] + zi];
	int bba = m_p[m_p[m_p[inc(xi)] + inc(yi)] + zi];
	int bab = m_p[m_p[m_p[inc(xi)] + yi] + inc(zi)];
	int bbb = m_p[m_p[m_p[inc(xi)] + inc(yi)] + inc(zi)];

	float x1 = lerp(grad(aaa, xf, yf, zf),
					grad(baa, xf - 1, yf, zf),
					u);
	float x2 = lerp(grad(aba, xf, yf - 1, zf),
					grad(bba, xf - 1, yf - 1, zf),
					u);
	float y1 = lerp(x1, x2, v);

	x1 = lerp(
		grad(aab, xf, yf, zf - 1),
		grad(bab, xf - 1, yf, zf - 1),
		u
	);
	
	x2 = lerp(
		grad(abb, xf, yf - 1, zf - 1),
		grad(bbb, xf - 1, yf - 1, zf - 1),
		u
	);
	
	float y2 = lerp(x1, x2, v);

	return (lerp(y1, y2, w) + 1) / 2;
}

float PerlinNoise::atOctave(phx::Vector3 pos, int octaves, float persitance)
{
	float tot = 0;
	float f = 1;
	float a = 1;
	float maxValue = 0;
	for (int i = 0; i < octaves; ++i)
	{
		tot += at(phx::Vector3(pos.x * f, pos.y * f, pos.z * f)) * a;
		maxValue += a;
		a *= persitance;
		f *= 2;
	}
	return tot / maxValue;
}
