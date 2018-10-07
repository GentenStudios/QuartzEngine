#include "engine/common.hpp"

#include "engine/voxels/chunk.hpp"

using namespace pheonix::voxels;

Chunk::Chunk()
{

}

Chunk::~Chunk()
{

}

Block Chunk::getBlock( int x, int y, int z )
{
    return m_blocks[x][y][z];
}
void Chunk::setBlock( int x, int y, int z, Block block )
{
    m_blocks[x][y][z] = block;
}
