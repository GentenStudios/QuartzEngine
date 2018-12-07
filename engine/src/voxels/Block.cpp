#include <engine/voxels/Block.hpp>
#include <algorithm>

using namespace phx::voxels;

RegistryBlock::RegistryBlock()
{
	m_blockID = "core:unknown";
	m_blockName = "Unknown Block";
	m_initialHealthPoints = 1;
	m_blockType = BlockType::SOLID;
}

RegistryBlock::RegistryBlock(std::string blockID, std::string blockName, int initialHP, BlockType blockType)
{
	m_blockID = blockID;
	m_blockName = blockName;
	m_initialHealthPoints = initialHP;
	m_blockType = blockType;
}

RegistryBlock::~RegistryBlock()
{}

const std::string& RegistryBlock::getBlockID() const { return m_blockID; }
const std::string& RegistryBlock::getBlockName() const { return m_blockName; }
BlockType RegistryBlock::getBlockType() const { return m_blockType; }

const BlockCallback& RegistryBlock::getPlaceCallback() const { return m_onPlaceCallback; }
const BlockCallback& RegistryBlock::getBreakCallback() const { return m_onBreakCallback; }
const InteractionCallback& RegistryBlock::getInteractLeftCallback() const { return m_interactLeftCallback; }
const InteractionCallback& RegistryBlock::getInteractRightCallback() const { return m_interactRightCallback; }

const std::vector<std::string>& RegistryBlock::getBlockTextures() const { return m_blockTextures; }

void phx::voxels::RegistryBlock::setBlockTextures(const std::vector<std::string>& textures) { m_blockTextures = textures; }

int RegistryBlock::getInitialHP() const { return m_initialHealthPoints; }

void RegistryBlock::setPlaceCallback(const BlockCallback& callback) { m_onPlaceCallback = callback; }
void RegistryBlock::setBreakCallback(const BlockCallback& callback) { m_onBreakCallback = callback; }
void RegistryBlock::setInteractLeftCallback(const InteractionCallback& callback) { m_interactLeftCallback = callback; }
void RegistryBlock::setInteractRightCallback(const InteractionCallback& callback) { m_interactRightCallback = callback; }

BlockInstance::BlockInstance()
{
	m_blockID = "core:unknown";

	auto& it = BlockLibrary::get()->requestBlock(m_blockID);
	m_hitpoints = it.getInitialHP();
	m_blockName = it.getBlockName();
	m_blockType = it.getBlockType();
	m_blockTextures = it.getBlockTextures();

}

BlockInstance::BlockInstance(const std::string& blockID)
{
	m_blockID = blockID;

	auto& it = BlockLibrary::get()->requestBlock(blockID);
	m_hitpoints = it.getInitialHP();
	m_blockName = it.getBlockName();
	m_blockType = it.getBlockType();
	m_blockTextures = it.getBlockTextures();
}

const std::string& BlockInstance::getBlockName() const { return m_blockName; }
void BlockInstance::setBlockName(const std::string& name) { m_blockName = name; }

unsigned int BlockInstance::getHitpoints() const { return m_hitpoints; }
void BlockInstance::setHitpoints(unsigned int hitpoints) { m_hitpoints = hitpoints; }

const std::string& BlockInstance::getBlockID() const { return m_blockID; }
BlockType BlockInstance::getBlockType() const { return m_blockType; }

const std::vector<std::string>& BlockInstance::getBlockTextures() const { return m_blockTextures; }
void BlockInstance::setBlockTextures(const std::vector<std::string>& newTextures) { m_blockTextures = newTextures; }

BlockLibrary* BlockLibrary::get()
{
	static BlockLibrary library;
	return &library;
}

void BlockLibrary::init()
{
	m_registeredBlocks["core:unknown"] = RegistryBlock("core:unknown", "Unkown Block", 1, BlockType::SOLID);
	m_registeredBlocks["core:out_of_bounds"] = RegistryBlock("core:out_of_bounds", "Out Of Bounds Block", 1, BlockType::GAS);
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

RegistryBlock BlockLibrary::requestBlock(const std::string& blockID) const
{
	auto it = m_registeredBlocks.find(blockID);

	if (it == m_registeredBlocks.end())
	{
		LWARNING("The Block: ", blockID, " cannot be found, but is being requested. Using core:unknown block type instead. Please take action!");
		return RegistryBlock("core:unknown", "Unknown Block", 1, BlockType::SOLID);
	}

	return it->second;
}