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
            static void init();

            /// @brief[in] Getter, Gets a block based off a set of coordinates in the chunk
            Block getBlock(int x, int y, int z);
            /// @breif[in] Setter, Sets the value of a block in a chunk
            void setBlock(int x, int y, int z, Block block);
        };
    }
}
