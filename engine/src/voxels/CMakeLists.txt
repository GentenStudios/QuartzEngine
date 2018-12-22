set(voxelSourceDir ${CMAKE_CURRENT_LIST_DIR})

set(voxelSources
    ${voxelSourceDir}/Block.cpp
    ${voxelSourceDir}/Chunk.cpp
    ${voxelSourceDir}/ChunkManager.cpp
)

set(entitySources
    ${voxelSourceDir}/entities/Item.cpp
    ${voxelSourceDir}/entities/ItemInstance.cpp
)

set(terrainSources
    ${voxelSourceDir}/terrain/PerlinNoise.cpp
)

source_group("Source Files\\Core\\Voxels" FILES ${voxelSources})
source_group("Source Files\\Core\\Voxels\\Entities" FILES ${entitySources})
source_group("Source Files\\Core\\Voxels\\Terrain" FILES ${terrainSources})

set(engineSources
    ${engineSources}
    ${voxelSources}
    ${entitySources}
    ${terrainSources}
    CACHE INTERNAL ""
)