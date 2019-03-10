set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(voxelHeaders
	${currentDir}/Block.hpp
	${currentDir}/Chunk.hpp
	${currentDir}/ChunkManager.hpp
	${currentDir}/Terrain/ITerrainGenerator.hpp
	${currentDir}/Terrain/PerlinNoise.hpp
	${currentDir}/Entities/Item.hpp
	${currentDir}/Entities/ItemInstance.hpp

	PARENT_SCOPE
)
