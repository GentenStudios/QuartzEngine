#include <engine/common.hpp>

#include <iostream>

#include <engine/voxels/block.hpp>
#include <engine/voxels/mapblock.hpp>

int main()
{
	phoenix::voxels::Block* nullBlock = new phoenix::voxels::Block("null", "null", phoenix::voxels::BlockType::SOLID);
	phoenix::voxels::Block* i1 = new phoenix::voxels::Block("core:wow", "wow", phoenix::voxels::BlockType::SOLID);
	phoenix::voxels::Block* i2 = new phoenix::voxels::Block("core:amazing", "amazing", phoenix::voxels::BlockType::SOLID);
	phoenix::voxels::Block* i3 = new phoenix::voxels::Block("core:ybw", "you better work", phoenix::voxels::BlockType::SOLID);
	phoenix::voxels::Block* i4 = new phoenix::voxels::Block("core:bitch", "bitch", phoenix::voxels::BlockType::SOLID);

	std::cout << phoenix::voxels::BlockLibrary::getBlockByID( i1->getID() ).getName() << std::endl;
	std::cout << phoenix::voxels::BlockLibrary::getBlockByID( i2->getID() ).getName() << std::endl;
	std::cout << phoenix::voxels::BlockLibrary::getBlockByID( i3->getID() ).getName() << std::endl;
	std::cout << phoenix::voxels::BlockLibrary::getBlockByID( i4->getID() ).getName() << std::endl;
	std::cout << phoenix::voxels::BlockLibrary::getBlockByID( "doesntexist" ).getName() << std::endl;
}
