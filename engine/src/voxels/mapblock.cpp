#include "engine/common.hpp"

#include "engine/voxels/block.hpp"
#include "engine/voxels/mapblock.hpp"

using namespace phoenix::voxels;

MapBlock::MapBlock( std::string id, int rotation ) : m_id( id ), m_rotation( rotation ), m_damage( 0 )
{
    // empty
}

MapBlock::~MapBlock()
{
    // empty
}

//Getters for universal data shared between all blocks
//something getTextures();

std::string MapBlock::getID() const
{
    return m_id;
}

// Getters and setters for unique block data
int MapBlock::getRotation() const
{
    return m_rotation;
};

void MapBlock::setRotation(int rotation)
{
    m_rotation = rotation;
};

int MapBlock::getDamage() const
{
    return m_damage;
};

void MapBlock::setDamage(int damage)
{
    m_damage = damage;
};
