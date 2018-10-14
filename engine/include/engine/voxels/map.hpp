#pragma once

#include <string>
#include "engine/voxels/chunk.hpp"

namespace pheonix {
    namespace voxels{

        class Map
        {
        public:
            Map();
            ~Map();

            /**
             * @brief getChunk
             * @param x
             * @param y
             * @param z
             * @return
             */
            Chunk getChunk(int x, int y, int z);

        private:
            /// 3 Dimensional Vector. Slightly funkier than a 3D array, but more flexible
            /// or maybe not, I don't know.
            std::vector< std::vector< std::vector< Chunk* > > > m_chunks;
        };
    }
}
