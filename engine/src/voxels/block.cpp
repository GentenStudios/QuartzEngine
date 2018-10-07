//
// Created by austin on 10/7/18.
//

#include "engine/common.hpp"

#include "engine/voxels/block.hpp"

using namespace pheonix;

void Block::init(std::string id, std::string name, std::string description, int rotation, BlockType type){
    this.id = id;
    this.name = name;
    this.description = description;
    this.rotation = rotation;
    this.type = type;

};

std::string Block::getID(){
    return this.id;
};

std::string Block::getName(){
    return this.name;
};

std::string Block::getDescription(){
    return this.description;
};

BlockType Block::getBlockType(){
    return this.type;
};

int Block::getRotation(){
    return this.rotation
};
void setRotation(int rotation){
    this.rotation = rotation;
};

Block getBlockByID{
    return NULL;
};