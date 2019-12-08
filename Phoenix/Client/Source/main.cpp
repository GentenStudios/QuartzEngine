#include <Core/Voxels/Blocks.hpp>
#include <Client/Main.hpp>
#include <iostream>
#include <stdio.h>

#undef main

using namespace phoenix;

int main(int argc, char* argv[])
{

    // ===== Launch core =====
    // Likely a single command from Quartz that launches the logger + any other critical tools

    // ===== Create main window + Display splash or terminal output =====

	// ===== Launch connection thread pointed at server =====
    // std::thread connection (Network::connection);

    // ===== Compare server mods.txt and local mods.txt, update if needed =====

    // ===== Load lua =====
	voxels::BlockRegistry::get()->registerBlock("core:dirt", "Dirt");
	voxels::BlockRegistry::get()->registerBlock("core:cobble", "CobbleStone");
	voxels::BlockRegistry::get()->registerBlock("core:stone", "Stone");
	// TODO: Replace these manual calls to register blocks with a call to run lua files based on what modules need loaded

    // ===== Launch renderer outputting to main window =====

	return 1;
};