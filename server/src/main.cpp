#include <engine/common.hpp>

#include <iostream>

#include <engine/voxels/block.hpp>
#include <engine/voxels/mapblock.hpp>

int main()
{
	pheonix::voxels::Block* nullBlock = new pheonix::voxels::Block("null", "null", pheonix::voxels::BlockType::SOLID);
	pheonix::voxels::Block* i1 = new pheonix::voxels::Block("core:wow", "wow", pheonix::voxels::BlockType::SOLID);
	pheonix::voxels::Block* i2 = new pheonix::voxels::Block("core:amazing", "amazing", pheonix::voxels::BlockType::SOLID);
	pheonix::voxels::Block* i3 = new pheonix::voxels::Block("core:ybw", "you better work", pheonix::voxels::BlockType::SOLID);
	pheonix::voxels::Block* i4 = new pheonix::voxels::Block("core:bitch", "bitch", pheonix::voxels::BlockType::SOLID);

	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( i1->getID() ).getName() << std::endl;
	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( i2->getID() ).getName() << std::endl;
	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( i3->getID() ).getName() << std::endl;
	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( i4->getID() ).getName() << std::endl;
	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( "doesntexist" ).getName() << std::endl;
}
