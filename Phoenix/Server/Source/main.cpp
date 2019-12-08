#include <Core/Voxels/Blocks.hpp>
#include <Server/Main.hpp>

#include <Quartz/Utilities/Commander.hpp>

#include <iostream>
#include <stdio.h>

#undef main

using namespace phoenix;

int main(int argc, char* argv[])
{

// ===== Launch core =====
    // Likely a single command from Quartz that launches the logger + any other critical tools

	// ===== Load Voxel data / Load lua =====
	std::cout << "Program started \n";
	//voxels::BlockRegistry *registry = registry->get();
	voxels::BlockRegistry::get()->registerBlock("core:dirt", "Dirt");
	voxels::BlockRegistry::get()->registerBlock("core:cobble", "CobbleStone");
	voxels::BlockRegistry::get()->registerBlock("core:stone", "Stone");
	// TODO: Replace these manual calls to register blocks with a call to run lua files

	std::cout << voxels::BlockRegistry::get()->getDisplayName(1);
	std::cout << std::to_string(voxels::BlockRegistry::get()->getBlockId("core::dirt"));

	// TODO: Replace these example functions with other, permanent, systems.
	//qz::utils::CommandBook commandBook = qz::utils::CommandBook();

	qz::utils::CommandBook::get()->add("getBlockName", 
					"Gets the name of a block based on provided ID number",
					"all",
					[](std::vector<std::string>&& args){
						std::cout << voxels::BlockRegistry::get()->getDisplayName(std::stoi(args[0]));
					});

	// ===== Load save data =====
	// Save::Load(argv[0]) //This will detect internally if a new map needs generated based on if save exists
	
// ===== Launch network connection listener =====
	// std::thread listener (Network::Listener);
	
// ===== Enter main loop watching for CLI input =====
	qz::utils::Commander kirk = qz::utils::Commander(std::cout, std::cin);
	kirk.post();

	// ===== Begin shutdown =====
	std::cout << "Begin Shutdown \n \n";

	// Send signal for listener to terminate
	// Confirm map has saved

	return 1;
};