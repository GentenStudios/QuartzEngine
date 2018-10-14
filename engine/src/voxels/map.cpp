#include "engine/common.hpp"

#include "engine/voxels/map.hpp"

using namespace pheonix::voxels;

Map::Map()
{

}

Map::~Map()
{

}

Chunk Map::getChunk( int x, int y, int z )
{
    return *m_chunks[x][y][z];
}