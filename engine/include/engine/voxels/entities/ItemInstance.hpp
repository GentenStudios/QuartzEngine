#pragma once

#include <engine/core/Core.hpp>
#include <engine/voxels/entities/Item.hpp>

namespace phx
{
	namespace entities
	{

		class ItemInstance
		{
		public:
			ItemInstance(std::string id);
			ItemInstance(std::string id, int baseDamage);
			~ItemInstance();

			// Getters for universal data shared between all items of this type
			// something getTextures();
			std::string getID() const;

			int getDamage() const;
			void setDamage(int damage);

		private:
			std::string m_id;
			int m_damage;
		};

	}
}
