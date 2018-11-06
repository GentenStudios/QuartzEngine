#include "engine/voxels/Block.hpp"

using namespace phx::voxels;

std::vector<Block*> BlockLibrary::m_blockLibrary;

Block::Block(std::string id, std::string name, BlockType type)
{
	m_id = id;
	m_name = name;
	m_blockType = type;
	BlockLibrary::registerBlock(this);
}

Block::Block(const Block& other)
{
	m_id = other.m_id;
	m_name = other.m_name;
	m_blockType = other.m_blockType;
	// no need to register the block again
}

Block::~Block()
{
	// empty
}

std::string Block::getID()
{
	return m_id;
}

std::string Block::getName()
{
	return m_name;
}

BlockType Block::getBlockType()
{
	return m_blockType;
}

/////////////////////////////////////////////
// Getters and setters for event callbacks //
/////////////////////////////////////////////

void Block::setOnPlaceCallback(BlockCallback callback) { m_onPlaceCallback = callback; }
BlockCallback Block::getOnPlaceCallback() { return m_onPlaceCallback; }

void Block::setOnBreakCallback(BlockCallback callback) { m_onBreakCallback = callback; }
BlockCallback Block::getOnBreakCallback() { return m_onBreakCallback; }

void Block::setOnInteractLeftCallback(BlockCallback callback) { m_onInteractLeftCallback = callback; }
BlockCallback Block::getOnInteractLeftCallback() { return m_onInteractLeftCallback; }

void Block::setOnInteractRightCallback(BlockCallback callback) { m_onInteractRightCallback = callback; }
BlockCallback Block::getOnInteractRightCallback() { return m_onInteractRightCallback; }


/////////////////////////////////////////////////////////////////
/////////////////// Block Library Code //////////////////////////
/////////////////////////////////////////////////////////////////

void BlockLibrary::registerBlock(Block* block)
{
	m_blockLibrary.push_back(block);
}

Block BlockLibrary::getBlockByID(std::string id)
{
	for (int i = 1; i < m_blockLibrary.size(); i++)
	{
		Block* block = m_blockLibrary[i];
		if (block->getID() == id)
		{
			return *block;
		}
	};

	return *(m_blockLibrary[0]);
}
