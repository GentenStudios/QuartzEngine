#include <Core/Voxels/Blocks.hpp>
#include <Server/Main.hpp>

#include <Quartz/Utilities/Commander.hpp>

#include <iostream>
#include <stdio.h>

#undef main

using namespace phoenix;

void testing(std::vector<std::string>&& args){std::cout << "FML";};

int main(int argc, char* argv[])
{

// ===== Launch core =====
    // Likely a single command from Quartz that launches the logger + any other critical tools

	// ===== Load Voxel data / Load lua =====
	std::cout << "Program started \n";
	//voxels::BlockRegistry *registry = registry->get();
	std::cout << "register dirt \n";
	voxels::BlockRegistry::get()->registerBlock("core:dirt", "Dirt");
	voxels::BlockRegistry::get()->registerBlock("core:cobble", "CobbleStone");
		std::cout << "WTF";
	voxels::BlockRegistry::get()->registerBlock("core:stone", "Stone");
	// TODO: Replace these manual calls to register blocks with a call to run lua files

	std::cout << "WTF";

	std::cout << voxels::BlockRegistry::get()->getDisplayName(1);
	std::cout << std::to_string(voxels::BlockRegistry::get()->getBlockId("core::dirt"));

	// TODO: Replace these example functions with other, permanent, systems.
	qz::utils::CommandBook commandBook = qz::utils::CommandBook();

	std::cout << "WTF";

	commandBook.add("getBlockName", 
					"Gets the name of a block based on provided ID number",
					"all", testing);
					/*[](std::vector<std::string>&& args){
						std::cout << voxels::BlockRegistry::get()->getDisplayName(std::stoi(args[1]));
					});*/

	/*commandBook.add("registerBlock", 
					"registers a block, \n first argument is the unique name, \n second argument is the display name",
					"all",
					[](std::vector<std::string>&& args){
						voxels::BlockRegistry::get()->registerBlock(args[1], args[2]);
						std::cout << "Block: " + args[2] + " Registered at: " + args[1];
					});*/

	// ===== Load save data =====
	// Save::Load(argv[0]) //This will detect internally if a new map needs generated based on if save exists
	
// ===== Launch network connection listener =====
	// std::thread listener (Network::Listener);
	
// ===== Enter main loop watching for CLI input =====
	/*bool run = true;
	while (run == true){
		// Listen for CLI instructions
	}*/

	// ===== Begin shutdown =====
	std::cout << "Begin Shutdown \n \n";

	// Send signal for listener to terminate
	// Confirm map has saved

	return 1;
};