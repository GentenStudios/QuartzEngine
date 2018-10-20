#include "engine/voxels/block.hpp"

using namespace phoenix::voxels;

std::vector<Block*> BlockLibrary::m_blockLibrary;

Block::Block( std::string id, std::string name, BlockType type )
{
    m_id = id;
    m_name = name;
    m_blockType = type;
    BlockLibrary::registerBlock(this);
};

Block::~Block()
{
    // empty
}

std::string Block::getID()
{
    return m_id;
};

std::string Block::getName()
{
    return m_name;
};

BlockType Block::getBlockType()
{
    return m_blockType;
};

void BlockLibrary::registerBlock(Block* block)
{
    m_blockLibrary.push_back(block);
}

Block BlockLibrary::getBlockByID(std::string id)
{
    for( int i = 1; i < m_blockLibrary.size(); i++ )
    {
        Block* block = m_blockLibrary[i];
        if ( block->getID() == id )
        {
            return *block;
        }
    };

    return *(m_blockLibrary[0]);
}
