#include <engine/voxels/Block.hpp>
#include <algorithm>

using namespace phx::voxels;

RegistryBlock::RegistryBlock()
{
	m_blockID = "Unknown";
	m_blockName = "Unknown";
	m_initialHealthPoints = 1;
}

RegistryBlock::RegistryBlock(std::string blockID, std::string blockName, int initialHP)
{
	m_blockID = blockID;
	m_blockName = blockName;
	m_initialHealthPoints = initialHP;
}

RegistryBlock::~RegistryBlock()
{}

void RegistryBlock::setPlaceCallback(BlockCallback& callback) { m_onPlaceCallback = callback; }
void RegistryBlock::setBreakCallback(BlockCallback callback) { m_onBreakCallback = callback; }

BlockLibrary* BlockLibrary::get()
{
	static BlockLibrary library;
	return &library;
}

void BlockLibrary::init(const RegistryBlock& unkownBlock)
{
	m_registeredBlocks["core:unknown"] = unkownBlock;
}

void BlockLibrary::registerBlock(const RegistryBlock& block)
{
	const char* blockID = block.getBlockID().c_str();

	if (m_registeredBlocks.find(blockID) != m_registeredBlocks.end())
	{
		LWARNING("The Block: ", blockID, " has already been registered, please take action!");
		return;
	}

	m_registeredBlocks[blockID] = block;
}

const RegistryBlock& BlockLibrary::requestBlock(const std::string& blockID)
{
	auto it = m_registeredBlocks.find(blockID);

	if (it == m_registeredBlocks.end())
	{
		LWARNING("The Block: ", blockID, " cannot be found, but is being requested, please take action!");
		return m_registeredBlocks["core:unknown"];
	}

	return it->second;
}
