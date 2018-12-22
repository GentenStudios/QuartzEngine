set(voxelIncludeDir ${CMAKE_CURRENT_LIST_DIR})

set(voxelHeaders
    ${voxelIncludeDir}/Block.hpp
    ${voxelIncludeDir}/Chunk.hpp
    ${voxelIncludeDir}/ChunkManager.hpp
)

set(entityHeaders
    ${voxelIncludeDir}/entities/Item.hpp
    ${voxelIncludeDir}/entities/ItemInstance.hpp
)

set(terrainHeaders
    ${voxelIncludeDir}/terrain/ITerrainGenerator.hpp
    ${voxelIncludeDir}/terrain/PerlinNoise.hpp
)

source_group("Header Files\\Voxels" FILES ${voxelHeaders})
source_group("Header Files\\Voxels\\Entities" FILES ${entityHeaders})
source_group("Header Files\\Voxels\\Terrain" FILES ${terrainHeaders})

set(engineHeaders
    ${engineHeaders}
    ${voxelHeaders}
    ${entityHeaders}
    ${terrainHeaders}
    CACHE INTERNAL "Global Engine Headers"
)