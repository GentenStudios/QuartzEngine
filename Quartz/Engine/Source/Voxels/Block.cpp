// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#include <Quartz/Core/QuartzPCH.hpp>
#include <Quartz/Voxels/Block.hpp>
#include <Quartz/Utilities/Logger.hpp>

using namespace qz::voxels;

RegistryBlock::RegistryBlock(const std::string& blockID, const std::string& blockName, int initialHP, BlockType blockType)
{
	m_blockID = blockID;
	m_blockName = blockName;
	m_initialHealthPoints = initialHP;
	m_blockType = blockType;
}

const std::string& RegistryBlock::getBlockID() const { return m_blockID; }

int RegistryBlock::getRegistryID() const
{
	return m_registryID;
}

const std::string& RegistryBlock::getBlockName() const { return m_blockName; }
BlockType RegistryBlock::getBlockType() const { return m_blockType; }

const BlockCallback& RegistryBlock::getPlaceCallback() const { return m_onPlaceCallback; }
const BlockCallback& RegistryBlock::getBreakCallback() const { return m_onBreakCallback; }
const InteractionCallback& RegistryBlock::getInteractLeftCallback() const { return m_interactLeftCallback; }
const InteractionCallback& RegistryBlock::getInteractRightCallback() const { return m_interactRightCallback; }

const std::vector<std::string>& RegistryBlock::getBlockTextures() const { return m_blockTextures; }

void RegistryBlock::setBlockTextures(const std::vector<std::string>& textures) { m_blockTextures = textures; }

int RegistryBlock::getInitialHP() const { return m_initialHealthPoints; }

void RegistryBlock::setPlaceCallback(const BlockCallback& callback) { m_onPlaceCallback = callback; }
void RegistryBlock::setBreakCallback(const BlockCallback& callback) { m_onBreakCallback = callback; }
void RegistryBlock::setInteractLeftCallback(const InteractionCallback& callback) { m_interactLeftCallback = callback; }
void RegistryBlock::setInteractRightCallback(const InteractionCallback& callback) { m_interactRightCallback = callback; }

BlockInstance::BlockInstance()
{
	auto it = BlockLibrary::get()->requestBlock(0); // requests core:unknown.
	m_hitpoints = it.getInitialHP();
	m_blockType = it.getBlockType();
	m_registryID = it.getRegistryID();
}

BlockInstance::BlockInstance(const std::string& blockID)
{
	auto it = BlockLibrary::get()->requestBlock(blockID);
	m_hitpoints = it.getInitialHP();
	m_blockType = it.getBlockType();
	m_registryID = it.getRegistryID();
}

BlockInstance::BlockInstance(int registryID)
{
	auto it = BlockLibrary::get()->requestBlock(registryID);
	m_hitpoints = it.getInitialHP();
	m_blockType = it.getBlockType();
	m_registryID = it.getRegistryID();
}

const std::string& BlockInstance::getBlockName() const { return BlockLibrary::get()->requestBlock(m_registryID).getBlockName(); }

unsigned int BlockInstance::getHitpoints() const { return m_hitpoints; }
void BlockInstance::setHitpoints(unsigned int hitpoints) { m_hitpoints = hitpoints; }

const std::string& BlockInstance::getBlockID() const { return BlockLibrary::get()->requestBlock(m_registryID).getBlockID(); }
BlockType BlockInstance::getBlockType() const { return m_blockType; }

const std::vector<std::string>& BlockInstance::getBlockTextures() const { return BlockLibrary::get()->requestBlock(m_registryID).getBlockTextures(); }

int BlockInstance::getRegistryID() const
{
	return m_registryID;
}

BlockLibrary* BlockLibrary::get()
{
	static BlockLibrary library;
	return &library;
}

void BlockLibrary::init()
{
	m_registeredBlocks.emplace("core:unknown", RegistryBlock{ "core:unknown", "Unknown Block", 1, BlockType::SOLID });
	m_registeredBlocks.emplace("core:out_of_bounds", RegistryBlock{ "core:out_of_bounds", "Out Of Bounds Block", 1, BlockType::GAS });
	m_registeredBlockAliases.emplace_back("core:unknown");
	m_registeredBlockAliases.emplace_back("core:out_of_bounds");
}

void BlockLibrary::registerBlock(RegistryBlock block)
{
	if (m_registeredBlocks.find(block.getBlockName()) != m_registeredBlocks.end())
	{
		LWARNING("The Block: ", block.getBlockName(), " has already been registered, please take action!");
		return;
	}

	block.m_registryID = m_registeredBlockAliases.size();
	m_registeredBlockAliases.emplace_back(block.getBlockID());
	m_registeredBlocks.emplace(block.getBlockID(), block);
}

const RegistryBlock& BlockLibrary::requestBlock(int registryID) const
{
	if (registryID == 0)
		return m_registeredBlocks.at("core:unknown");
	
	if (registryID == 1)
		return m_registeredBlocks.at("core:out_of_bounds");

	if (static_cast<std::size_t>(registryID) >= m_registeredBlockAliases.size())
	{
		LWARNING("The Block: ", registryID, " cannot be found, but is being requested. Using core:unknown block type instead. Please take action!");
		return m_registeredBlocks.at("core:unknown");
	}

	return m_registeredBlocks.at(m_registeredBlockAliases[registryID]);
}

const RegistryBlock& BlockLibrary::requestBlock(const std::string& blockID) const
{
	const auto it = m_registeredBlocks.find(blockID);
	if (it == m_registeredBlocks.end())
	{
		LWARNING("The Block: ", blockID, " cannot be found, but is being requested. Using core:unknown block type instead. Please take action!");
		return m_registeredBlocks.at("core:unknown");
	}

	return it->second;
}
