#pragma once

#include <string>

namespace pheonix {

    namespace voxels {

        class MapBlock {
        public:
            //Getters for universal data shared between all blocks
            //something getTextures();
            std::string getName();

            //Getters and setters for unique block data
            int getRotation();
            void setRotation(int rotation);

            int getDamage();
            int setDamage(int damage);

        private:
            std::string m_id;
            int rotation;
            int damage;
        };
    }
}