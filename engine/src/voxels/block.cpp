//
// Created by austin on 10/7/18.
//

#include "engine/common.hpp"

#include "engine/voxels/block.hpp"

using namespace pheonix;

void Block:init(std::string id, std::string name, std::string description,
int rotation, BlockType type){

    this.id = id;
    this.name = name;
    this.description = description;
    this.rotation = rotation;
    this.type = type;

};