#pragma once

#include <string>
#include "engine/voxels/block.hpp"

namespace pheonix {
    namespace voxels{

        class Chunk
        {
        public:
            Chunk();
            ~Chunk();

            /**
             * @brief getBlock
             * @param x
             * @param y
             * @param z
             * @return
             */
            Block getBlock(int x, int y, int z);

            /**
             * @brief setBlock
             * @param x
             * @param y
             * @param z
             * @param block
             */
            void setBlock(int x, int y, int z, Block block);
        private:
            Block m_blocks[16][16][256];
        };
    }
}
