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

source_group("Header Files\\Voxels" FILES ${voxelHeaders})
source_group("Header Files\\Voxels\\Entities" FILES ${entityHeaders})

set(engineHeaders
    ${engineHeaders}
    ${voxelHeaders}
    ${entityHeaders}
    CACHE INTERNAL "Global Engine Headers"
)