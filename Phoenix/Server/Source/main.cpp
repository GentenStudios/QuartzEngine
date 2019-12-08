#include <Core/Voxels/Blocks.hpp>
#include <Server/Main.hpp>
#include <iostream>
#include <stdio.h>

#undef main

using namespace phoenix;

int main(int argc, char* argv[])
{

    // ===== Launch core =====
    // Likely a single command from Quartz that launches the logger + any other critical tools
	std::cout << "Program started \n";

	// ===== Load Voxel data / Load lua =====

	voxels::BlockRegistry::get()->registerBlock("core:dirt", "Dirt");
	voxels::BlockRegistry::get()->registerBlock("core:cobble", "CobbleStone");
	voxels::BlockRegistry::get()->registerBlock("core:stone", "Stone");
	// TODO: Replace these manual calls to register blocks with a call to run lua files

	std::cout << voxels::BlockRegistry::get()->getDisplayName(1);
	std::cout << std::to_string(voxels::BlockRegistry::get()->getBlockId("core::dirt"));
	std::cout << std::to_string(voxels::BlockRegistry::get()->getBlockId("core:dirt"));
	std::cout << std::to_string(voxels::BlockRegistry::get()->getBlockId("core:stone"));
	std::cout << "\nCobbleStone1844674407370955161502\n";
	// TODO: Replace these calls with unit tests

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