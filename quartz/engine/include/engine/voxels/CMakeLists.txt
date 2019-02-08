set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(voxelHeaders
	${currentDir}/Block.hpp
	${currentDir}/Chunk.hpp
	${currentDir}/ChunkManager.hpp
	${currentDir}/terrain/ITerrainGenerator.hpp
	${currentDir}/terrain/PerlinNoise.hpp
	${currentDir}/entities/Item.hpp
	${currentDir}/entities/ItemInstance.hpp
)
