#pragma once

#include <string>
#include <vector>

namespace pheonix {

    namespace voxels{

        m_blockLibrary std::vector<Block>;

        /// @brief This defines what state of matter the block is
        enum class BlockType
        {
            GAS,    ///< Gas Blocks are, for example, Air, or Oxygen if implemented.
            LIQUID, ///< Fluid Liquid Dynamics are applied to these blocks.
            SOLID,  ///< Generic Stable Block, used for most things.
        };

        class Block
        {
        public:
            /**
             * @brief Initialise a block
             * @param[in] The unique id for the block, should be in format mod:id to eliminate conflict
             * @param[in] The player friendly name of the block
             * @param[in] A short description of what the block is
             * @param[in] The state of block rotation
             * @param[in] The block type (SOLID, LIQUID, GAS)
             */
            Block( std::string id, std::string name, BlockType type );
            ~Block();

            /**
             * @brief getID - getID of Block
             * @return Return a string for the ID of the block
             */
            std::string getID();

            /**
             * @brief getName - Get name of block
             * @return Return a string of the name of the block
             */
            std::string getName();

            /// @brief[in] Getter, Returns the block type (Solid, Liquid, Gas)
            BlockType getBlockType();

            //??????? getTextures();

        private:
            /// @brief Unique id using the convention mod:name
            std::string m_id;
            /// @brief Name that will display to the user
            std::string m_name;
            /// @brief Short description of the block
            BlockType m_blockType;
            //??????? textures; //String? Array of strings? Array of file pointers? Image class?
        };

        Block getBlockByID(std::string id);

    }

}
