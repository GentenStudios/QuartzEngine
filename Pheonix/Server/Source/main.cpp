#include <Server/Main.hpp>
#include <Core/Voxels/Blocks.hpp>
#include <stdio.h>
#include <iostream>

#undef main

using namespace pheonix;

int main()
{
  voxels::BlockRegistry registry = voxels::BlockRegistry();
  registry.registerBlock("core:dirt", "Dirt");
  registry.registerBlock("core:cobble", "CobbleStone");
  registry.registerBlock("core:stone", "Stone"); 

  std::cout << registry.getDisplayName(1) << "\n";
  std::cout << registry.getDisplayName(2) << "\n";
  std::cout << registry.getDisplayName(3) << "\n";

  std::cout << registry.getBlockId("core:stone") << "\n";
  std::cout << registry.getBlockId("asdfadsf") << "\n";
  std::cout << registry.getBlockId("core:dirt") << "\n";

  return 0;
};