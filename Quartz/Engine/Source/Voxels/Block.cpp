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
#include <Quartz/Core/Utilities/Logger.hpp>

using namespace qz::voxels;

RegistryBlock::RegistryBlock(std::string blockID, std::string blockName, int initialHP, BlockType blockType)
{
	m_blockID = blockID;
	m_blockName = blockName;
	m_initialHealthPoints = initialHP;
	m_blockType = blockType;
}

const std::string& RegistryBlock::getBlockID() const { return m_blockID; }
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

BlockInstance::BlockInstance() :
	m_blockID("core:unknown")
{
	auto it = BlockLibrary::get()->requestBlock(m_blockID);
	m_hitpoints = it.getInitialHP();
	m_blockType = it.getBlockType();
}

BlockInstance::BlockInstance(const std::string& blockID) :
	m_blockID(blockID)
{
	auto it = BlockLibrary::get()->requestBlock(blockID);
	m_hitpoints = it.getInitialHP();
	m_blockType = it.getBlockType();
	m_blockName = it.getBlockName();
}

const std::string& BlockInstance::getBlockName() const { return m_blockName; }
void BlockInstance::setBlockName(const std::string& name) { m_blockName = name; }

unsigned int BlockInstance::getHitpoints() const { return m_hitpoints; }
void BlockInstance::setHitpoints(unsigned int hitpoints) { m_hitpoints = hitpoints; }

const std::string& BlockInstance::getBlockID() const { return m_blockID; }
BlockType BlockInstance::getBlockType() const { return m_blockType; }

const std::vector<std::string>& BlockInstance::getBlockTextures() const { return BlockLibrary::get()->requestBlock(m_blockID).getBlockTextures(); }

BlockLibrary* BlockLibrary::get()
{
	static BlockLibrary library;
	return &library;
}

void BlockLibrary::init()
{
	m_registeredBlocks.emplace("core:unknown", RegistryBlock{ "core:unknown", "Unkown Block", 1, BlockType::SOLID });
	m_registeredBlocks.emplace("core:out_of_bounds", RegistryBlock{ "core:out_of_bounds", "Out Of Bounds Block", 1, BlockType::GAS });
}

void BlockLibrary::registerBlock(const RegistryBlock& block)
{
	const char* blockID = block.getBlockID().c_str();

	if (m_registeredBlocks.find(blockID) != m_registeredBlocks.end())
	{
		LWARNING("The Block: ", blockID, " has already been registered, please take action!");
		return;
	}

	m_registeredBlocks.emplace(blockID, block);
}

const RegistryBlock& BlockLibrary::requestBlock(const std::string& blockID) const
{
	auto it = m_registeredBlocks.find(blockID);

	if (it == m_registeredBlocks.end())
	{
		LWARNING("The Block: ", blockID, " cannot be found, but is being requested. Using core:unknown block type instead. Please take action!");
		return m_registeredBlocks.at("core:unknown");
	}

	return it->second;
}
