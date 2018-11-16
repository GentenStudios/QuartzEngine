#include <engine/voxels/Block.hpp>

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

/////////////////////////////////////////////
// Getters for Block Data ///////////////////
/////////////////////////////////////////////

const std::string& Block::getID() const
{
	return m_id;
}

const std::string& Block::getName() const
{
	return m_name;
}

BlockType Block::getBlockType() const
{
	return m_blockType;
}

/////////////////////////////////////////////
// Getters and setters for event callbacks //
/////////////////////////////////////////////

void Block::setOnPlaceCallback(BlockCallback callback) { m_onPlaceCallback = callback; }
const BlockCallback& Block::getOnPlaceCallback() const { return m_onPlaceCallback; }

void Block::setOnBreakCallback(BlockCallback callback) { m_onBreakCallback = callback; }
const BlockCallback& Block::getOnBreakCallback() const { return m_onBreakCallback; }

void Block::setOnInteractLeftCallback(BlockCallback callback) { m_onInteractLeftCallback = callback; }
const BlockCallback& Block::getOnInteractLeftCallback() const { return m_onInteractLeftCallback; }

void Block::setOnInteractRightCallback(BlockCallback callback) { m_onInteractRightCallback = callback; }
const BlockCallback& Block::getOnInteractRightCallback() const { return m_onInteractRightCallback; }


/////////////////////////////////////////////////////////////////
/////////////////// Block Library Code //////////////////////////
/////////////////////////////////////////////////////////////////

void BlockLibrary::registerBlock(Block* block)
{
	m_blockLibrary.push_back(block);
}

Block BlockLibrary::getBlockByID(std::string id)
{
	for (unsigned int i = 1; i < m_blockLibrary.size(); i++)
	{
		Block* block = m_blockLibrary[i];
		if (block->getID() == id)
		{
			return *block;
		}
	};

	return *(m_blockLibrary[0]);
}
