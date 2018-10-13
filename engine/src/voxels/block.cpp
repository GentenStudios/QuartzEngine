#include "engine/common.hpp"

#include "engine/voxels/block.hpp"

using namespace pheonix::voxels;

Block::Block( std::string id, std::string name, BlockType type )
{
    this->m_id = id;
    this->m_name = name;
    this->m_blockType = type;
    m_blockLibrary.insert(this);
};

std::string Block::getID()
{
    return this->m_id;
};

std::string Block::getName()
{
    return this->m_name;
};

BlockType Block::getBlockType()
{
    return this->m_blockType;
};

getBlockByID(std:string id){
    for(int i=0; i < m_blockLibrary.size(); i++){
        if (m_blockLibrary[i].m_id == id){
            return m_blockLibrary[i];
        }
    }
    return NULL;
};