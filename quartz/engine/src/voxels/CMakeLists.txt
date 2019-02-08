set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(voxelSources
	${currentDir}/Block.cpp
	${currentDir}/Chunk.cpp
	${currentDir}/ChunkManager.cpp

	${currentDir}/entities/Item.cpp
	${currentDir}/entities/ItemInstance.cpp

	${currentDir}/terrain/PerlinNoise.cpp

	PARENT_SCOPE
)