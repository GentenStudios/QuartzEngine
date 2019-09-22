#include <Server/Main.hpp>
#include <Core/Voxels/Blocks.hpp>

#undef main

using namespace pheonix;

int main()
{
  voxels::BlockRegistry registry = voxels::BlockRegistry();
  registry.registerBlock("core:dirt", "Dirt");
  registry.registerBlock("core:cobble", "CobbleStone");
  registry.registerBlock("core:stone", "Stone");

  printf(registry.getBlockByID(1).getDisplayName);
  return 0;
};