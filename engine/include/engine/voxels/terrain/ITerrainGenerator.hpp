#include <engine/core/Core.hpp>

#include <engine/core/math/Vector3.hpp>

namespace phx
{
	namespace voxels
	{

		class ITerrainGenerator
		{
		public:
			ITerrainGenerator();
			virtual ~ITerrainGenerator();

			virtual void init() = 0;
			virtual void generateFor(phx::Vector3 pos) = 0;
		};

	}
}