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
#include <quartz/voxels/entities/Item.hpp>

using namespace qz::entities;

std::vector<Item*> ItemLibrary::m_itemLibrary;

Item::Item(std::string id, std::string name)
{
	m_id = id;
	m_name = name;
	ItemLibrary::registerItem(this);
};

Item::~Item()
{
	// empty
}

std::string Item::getID()
{
	return m_id;
};

std::string Item::getName()
{
	return m_name;
};

void Item::setOnBreakCallback(void* callback) { m_onBreakCallback = callback; }
void* Item::getOnBreakCallback() { return m_onBreakCallback; }

void Item::setOnUseCallback(void* callback) { m_onUseCallback = callback; }
void* Item::getOnUseCallback() { return m_onUseCallback; }

/////////////////////////////////////////////////////////////////
/////////////////// Block Library Code //////////////////////////
/////////////////////////////////////////////////////////////////

void ItemLibrary::registerItem(Item* item)
{
	m_itemLibrary.push_back(item);
}

Item ItemLibrary::getItemByID(std::string id)
{
	for (int i = 1; i < m_itemLibrary.size(); i++)
	{
		Item* item = m_itemLibrary[i];
		if (item->getID() == id)
		{
			return *item;
		}
	};

	return *(m_itemLibrary[0]);
}

