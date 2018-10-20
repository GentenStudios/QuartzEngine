#pragma once

#include "engine/common.hpp"

namespace phoenix {

	namespace voxels {

		class MapBlock {
		public:
			MapBlock(std::string id, int rotation);
			~MapBlock();

			// Getters for universal data shared between all blocks
			// something getTextures();
			std::string getID() const;

			// Getters and setters for unique block data
			int getRotation() const;
			void setRotation(int rotation);

			int getDamage() const;
			void setDamage(int damage);

		private:
			std::string m_id;
			int m_rotation;
			int m_damage;
		};
	}
}