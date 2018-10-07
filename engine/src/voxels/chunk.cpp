//
// Created by austin on 10/7/18.
//

#include "engine/common.hpp"

#include "engine/voxels/chunk.hpp"

using namespace pheonix;

void Chunk::init(){

}

Block Chunk::getBlock(int x, int y, int z){
    return blocks[x][y][z];
}
void Chunk::setBlock(int x, int y, int z, Block block){
    blocks[x][y][z] = block;
}