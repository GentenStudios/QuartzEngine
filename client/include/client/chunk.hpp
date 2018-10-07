#pragma once

#include <engine/common.hpp>

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace pheonix {
    namespace graphics {

        enum class BlockFace
        {
            FRONT,
            BACK,
            RIGHT,
            LEFT,
            BOTTOM,
            TOP
        };

        enum class BlockType
        {
            EMPTY,
            SOLID,
        };

        class Chunk
        {
        public:
            Chunk();
            ~Chunk();

            inline unsigned int getVAO() const { return m_vertArrayObject; }
            inline unsigned int getVBO() const { return m_vertBufferObject; }

            void populateChunk( unsigned int chunkSize );
            void build();
            void draw();

            void blockPlaceAt( int x, int y, int z );
            void blockDestroyAt( int x, int y, int z );
            BlockType blockExists( float x, float y, float z );

        private:
            void clearOpenGL();
            void setChunkSize( unsigned int chunkSize );

            void blockAddFace(glm::vec3* vertices, int x, int y, int z, BlockFace face);
            void blockRemoveFace(glm::vec3* vertices, int x, int y, int z, BlockFace face);

            unsigned int m_vertArrayObject, m_vertBufferObject, m_uvBufferObject;
            unsigned int m_shaderProgram;

            int m_chunkSize, m_vertsInChunk, m_uvsInChunk;

            bool m_populated;

            const int vertInCube = 36;
            const int uvInCube = 36;

            /// @brief 3-Dimensional Array of vector inside vector inside vector,
            /// for an overall layout like m_chunkBlocks[x][y][z]
            std::vector< std::vector< std::vector< BlockType > > > m_chunkBlocks;
        };

    }
}
