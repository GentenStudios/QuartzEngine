#include <Core/Voxels/Blocks.hpp>
#include <Server/Main.hpp>

#include <Quartz/Utilities/Commander.hpp>

#include <iostream>
#include <stdio.h>

#undef main

using namespace pheonix;

int main()
{
	voxels::BlockRegistry registry = voxels::BlockRegistry();
	registry.registerBlock("core:dirt", "Dirt");
	registry.registerBlock("core:cobble", "CobbleStone");
	registry.registerBlock("core:stone", "Stone");

	qz::utils::CommandBook commandBook;
	qz::utils::Commander commandPost = qz::utils::Commander(commandBook, std::cout, std::cin);

	int getBlockNameCommander(std::vector<std::string>&& args){
		std::cout << registry.getDisplayName(args[1]);
	}
	commandBook.add("getBlockName", 
					"Gets the name of a block based on provided ID number",
					"all",
					getBlockNameCommander);
	int registerBlockCommander(std::vector<std::string>&& args){
		std::cout << registry.getDisplayName(args[1]);
	}
	commandBook.add("getBlockName", 
					"Gets the name of a block based on provided ID number",
					"all",
					getBlockNameCommander);

	std::cout << registry.getDisplayName(1) << "\n";
	std::cout << registry.getDisplayName(2) << "\n";
	std::cout << registry.getDisplayName(3) << "\n";

	std::cout << registry.getBlockId("core:stone") << "\n";
	std::cout << registry.getBlockId("asdfadsf") << "\n";
	std::cout << registry.getBlockId("core:dirt") << "\n";

	return 0;
};