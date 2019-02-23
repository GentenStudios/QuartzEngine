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

#include <quartz/core/QuartzPCH.hpp>
#include <quartz/voxels/entities/ItemInstance.hpp>

using namespace qz::entities;

// JUST HERE FOR REFERENCE. NOT NEEDED FOR ANYTHING ATM.
// MapBlock::MapBlock( std::string id, int rotation ) : m_id( id ), m_rotation( rotation ), m_damage( 0 )

ItemInstance::ItemInstance(std::string id) : m_damage(0), m_id(id)
{
    // empty
}

ItemInstance::ItemInstance(std::string id, int baseDamage) : m_damage(baseDamage), m_id(id)
{
    // empty
}

ItemInstance::~ItemInstance()
{
    // empty
}

// Getters for universal data shared between all blocks
// something getTextures();

std::string ItemInstance::getID() const
{
    return m_id;
}

// Getters and setters for unique item data

int ItemInstance::getDamage() const
{
    return m_damage;
};

void ItemInstance::setDamage(int damage)
{
    m_damage = damage;
};

