#include "engine/voxels/block.hpp"

using namespace pheonix::voxels;

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

/////////////////////////////////////////////
// Getters and setters for event callbacks //
/////////////////////////////////////////////

void Block::setOnPlaceCallback(void* callback) { m_onPlaceCallback = callback; }
void* Block::getOnPlaceCallback() { return m_onPlaceCallback; }

void Block::setOnBreakCallback(void* callback) { m_onBreakCallback = callback; }
void* Block::getOnBreakCallback() { return m_onBreakCallback; }

void Block::setOnInteractLeftCallback(void* callback) { m_onInteractLeftCallback = callback; }
void* Block::getOnInteractLeftCallback() { return m_onInteractLeftCallback; }

void Block::setOnInteractRightCallback(void* callback) { m_onInteractRightCallback = callback; }
void* Block::getOnInteractRightCallback() { return m_onInteractRightCallback; }


/////////////////////////////////////////////////////////////////
/////////////////// Block Library Code //////////////////////////
/////////////////////////////////////////////////////////////////

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
