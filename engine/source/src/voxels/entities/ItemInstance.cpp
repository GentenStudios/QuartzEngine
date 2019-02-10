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
