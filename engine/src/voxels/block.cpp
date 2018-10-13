#include "engine/common.hpp"

#include "engine/voxels/block.hpp"

using namespace pheonix::voxels;

Block::Block( std::string id, std::string name, BlockType type )
{
    this->m_id = id;
    this->m_name = name;
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

BlockType Block::getBlockType()
{
    return this->m_blockType;
};
