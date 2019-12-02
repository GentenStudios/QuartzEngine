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

	// ===== Load Voxel data / Load lua =====
	voxels::BlockRegistry registry = voxels::BlockRegistry();
	registry.registerBlock("core:dirt", "Dirt");
	registry.registerBlock("core:cobble", "CobbleStone");
	registry.registerBlock("core:stone", "Stone");
	// TODO: Replace these manual calls to register blocks with a call to run lua files

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

	// Send signal for listener to terminate
	// Confirm map has saved

	return 1;
};