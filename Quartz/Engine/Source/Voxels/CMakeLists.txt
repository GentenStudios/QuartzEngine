set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(voxelSources
	${currentDir}/Block.cpp
	#	${currentDir}/Chunk.cpp
	#	${currentDir}/ChunkManager.cpp

  #${currentDir}/Chunk.cpp
	#${currentDir}/ChunkRenderer.cpp
	#${currentDir}/ChunkManager.cpp

	${currentDir}/Entities/Item.cpp
	${currentDir}/Entities/ItemInstance.cpp

	${currentDir}/Terrain/PerlinNoise.cpp

	PARENT_SCOPE
)
