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
