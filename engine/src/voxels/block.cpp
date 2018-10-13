#include "engine/voxels/block.hpp"

using namespace pheonix::voxels;

Block::Block( std::string id, std::string name, BlockType type )
{
    this->m_id = id;
    this->m_name = name;
    this->m_blockType = type;
};

Block::~Block()
{
    // empty
}

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

BlockRegistry::BlockRegistry()
{
}

BlockRegistry::~BlockRegistry()
{
    // empty
}

Block BlockRegistry::getBlockByID(std::string id)
{
    for( int i = 1; i < m_blockLibrary.size(); i++ )
    {
        Block* block = m_blockLibrary[i];
        if ( block->getID() == id )
        {
            return *block;
        }
        
        return *block;
    };
}

void BlockRegistry::registerBlock(Block* block)
{
    m_blockLibrary.push_back(block);
}
