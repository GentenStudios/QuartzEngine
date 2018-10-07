#include "engine/common.hpp"

#include "engine/voxels/block.hpp"

using namespace pheonix::voxels;

Block::Block( std::string id, std::string name, std::string description, int rotation, BlockType type )
{
    this->m_id = id;
    this->m_name = name;
    this->m_description = description;
    this->m_rotation = rotation;
    this->m_blockType = type;
};

std::string Block::getID()
{
    return this->m_id;
};

std::string Block::getName()
{
    return this->m_name;
};

std::string Block::getDescription()
{
    return this->m_description;
};

BlockType Block::getBlockType()
{
    return this->m_blockType;
};

int Block::getRotation()
{
    return this->m_rotation;
};

void Block::setRotation( int rotation )
{
    this->m_rotation = rotation;
};
