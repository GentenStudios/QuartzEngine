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

  //std::string output = "test"; // registry.getDisplayName(1);

  //printf("%s", output);
  return 0;
};