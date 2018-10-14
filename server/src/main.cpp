#include <engine/common.hpp>

#include <iostream>

#include <engine/voxels/block.hpp>
#include <engine/voxels/mapblock.hpp>

int main()
{
	pheonix::voxels::Block* nullBlock = new pheonix::voxels::Block("null", "null", pheonix::voxels::BlockType::SOLID);
	pheonix::voxels::Block* grassBlock = new pheonix::voxels::Block("123456789", "Grass", pheonix::voxels::BlockType::SOLID);

	pheonix::voxels::MapBlock randomBlock( "123456789", 0 );
	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( randomBlock.getID() ).getName() << std::endl;
}
