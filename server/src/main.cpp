#include <engine/common.hpp>

#include <iostream>

#include <engine/voxels/block.hpp>
#include <engine/voxels/mapblock.hpp>
#include <engine/entities/item.hpp>
#include <engine/entities/iteminstance.hpp>

int main()
{
	pheonix::voxels::Block* nullBlock = new pheonix::voxels::Block("null", "null", pheonix::voxels::BlockType::SOLID);
	pheonix::voxels::Block* b1 = new pheonix::voxels::Block("core:wow", "wow", pheonix::voxels::BlockType::SOLID);
	pheonix::voxels::Block* b2 = new pheonix::voxels::Block("core:amazing", "amazing", pheonix::voxels::BlockType::SOLID);
	pheonix::voxels::Block* b3 = new pheonix::voxels::Block("core:ybw", "you better work", pheonix::voxels::BlockType::SOLID);
	pheonix::voxels::Block* b4 = new pheonix::voxels::Block("core:bitch", "bitch", pheonix::voxels::BlockType::SOLID);

	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( b1->getID() ).getName() << std::endl;
	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( b2->getID() ).getName() << std::endl;
	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( b3->getID() ).getName() << std::endl;
	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( b4->getID() ).getName() << std::endl;
	std::cout << pheonix::voxels::BlockLibrary::getBlockByID( "doesntexist" ).getName() << std::endl;
	
	pheonix::entities::Item* nullItem = new pheonix::entities::Item("null", "null");
	pheonix::entities::Item* i1 = new pheonix::entities::Item("dishes:fork", "Fork");
	pheonix::entities::Item* i2 = new pheonix::entities::Item("core:dirt", "Dirt");
	pheonix::entities::Item* i3 = new pheonix::entities::Item("core:cobblestone", "Cobblestone");
	pheonix::entities::Item* i4 = new pheonix::entities::Item("tools:shovel", "Shovel");

	std::cout << pheonix::entities::ItemLibrary::getItemByID( "dishes:fork" ).getName() << std::endl;
	std::cout << pheonix::entities::ItemLibrary::getItemByID( "core:dirt" ).getName() << std::endl;
	std::cout << pheonix::entities::ItemLibrary::getItemByID( "core:cobblestone" ).getName() << std::endl;
	std::cout << pheonix::entities::ItemLibrary::getItemByID( "tools:shovel" ).getName() << std::endl;
	std::cout << pheonix::entities::ItemLibrary::getItemByID( "dne" ).getName() << std::endl;
}