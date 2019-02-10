#pragma once

#include <quartz/core/math/Vector3.hpp>

namespace qz
{
	namespace voxels
	{

		class ITerrainGenerator
		{
		public:
			ITerrainGenerator();
			virtual ~ITerrainGenerator();

			virtual void init() = 0;
			virtual void generateFor(qz::Vector3 pos) = 0;
		};

	}
}