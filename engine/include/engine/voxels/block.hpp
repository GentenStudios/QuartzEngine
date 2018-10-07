//
// Created by austin on 10/7/18.
//

#pragma once

#include <string>

namespace pheonix {

    namespace voxels{

        class Block{

        private:
            std::string id; //Unique id using the convention mod:name
            std::string name; //Name that will display to the user
            std::string description; //Short description of the block
            int rotation; //Direction block is facing
            int state; //State of the block???
            ??????? textures; //String? Array of strings? Array of file pointers? Image class?

        public:
            Block(std::string id, std::string name, std::string description,
                  int rotation, int state, ???? textures){

            };
            std::string getID;
            std::string getName;
            std::string getDescription;
            int getState;
            int getRotation;
            ??????? getTextures;
        };

        Block getBlockByID(std::string id);
    }

}