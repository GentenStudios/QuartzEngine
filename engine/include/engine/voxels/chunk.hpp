//
// Created by austin on 10/7/18.
//

#pragma once

#include <string>
#include "engine/voxels/block.hpp"

namespace pheonix {
    namespace voxels{
        class chunk{

        private:
            Block blocks[16][16][256];

        public:
            Block getBlock(int x, int y, int z);
            Block setBlock(int x, int y, int z, Block block);
        };
    }
}
