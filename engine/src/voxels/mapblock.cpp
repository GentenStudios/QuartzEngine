#include "engine/common.hpp"

#include "engine/voxels/block.hpp"

using namespace pheonix::voxels;

MapBlock::MapBlock( std::string id, int rotation)
{
    this->m_id = id;
    this->m_rotation = rotation;
    this->m_damage = 0;
};

//Getters for universal data shared between all blocks
//something getTextures();
std::string getName(){
    //Some function to get the name of the block from the parent
};

//Getters and setters for unique block data
int getRotation(){
    return this->m_rotation;
};
void setRotation(int rotation){
    this->m_rotation = rotation;
};

int getDamage(){
    return this->m_damage;
};
int setDamage(int damage){
    this->damage = damage;
};