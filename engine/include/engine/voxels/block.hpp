//
// Created by austin on 10/7/18.
//

#pragma once

#include <string>

namespace pheonix {

    namespace voxels{

        enum class BlockType
        {
            GAS,
            LIQUID,
            SOLID,
        };

        class Block{

        private:
            std::string id; //Unique id using the convention mod:name
            std::string name; //Name that will display to the user
            std::string description; //Short description of the block
            int rotation; //Direction block is facing
            BlockType blockType; //What type of block are we dealing with?
            //??????? textures; //String? Array of strings? Array of file pointers? Image class?

        public:
            Block(std::string id, std::string name, std::string description,
                  int rotation, BlockType type);

            std::string getID();
            std::string getName();
            std::string getDescription();
            BlockType getBlockType();
            int getRotation();
            void setRotation(int rotation);
            //??????? getTextures();
        };

        Block getBlockByID(std::string id);
    }

}