//
// Created by austin on 10/7/18.
//

#pragma once

#include <string>

namespace pheonix {

    namespace voxels{

        /** @brief This defines what state of matter the block is
         */
        enum class BlockType
        {
            GAS,
            LIQUID,
            SOLID,
        };

        class Block{

        private:
            /// @breif Unique id using the convention mod:name
            std::string id;
            /// @breif Name that will display to the user
            std::string name;
            /// @breif Short description of the block
            std::string description;
            /// @breif Direction block is facing
            int rotation;
            /// @breif What type of block are we dealing with?
            BlockType blockType;
            //??????? textures; //String? Array of strings? Array of file pointers? Image class?

        public:
            /**
             * @brief Initialise a block
             * @param[in] The unique id for the block, should be in format mod:id to eliminate conflict
             * @param[in] The player friendly name of the block
             * @param[in] A short description of what the block is
             * @param[in] The state of block rotation
             * @param[in] The block type (SOLID, LIQUID, GAS)
             */
            static void init(std::string id, std::string name, std::string description, int rotation, BlockType type);

            /// @breif[in] Getter, returns the unique id of the block
            std::string getID();

            /// @breif[in] Getter, returns the player friendly name of the block
            std::string getName();

            /// @breif[in] Getter, returns the breif block description
            std::string getDescription();

            /// @breif[in] Getter, Returns the block type (Solid, Liquid, Gas)
            BlockType getBlockType();

            /// @breif[in] Getter, Returns the rotation value of the block
            int getRotation();
            /// @breif[in] Setter, Sets the rotation value of the block
            void setRotation(int rotation);

            //??????? getTextures();
        };


        /// @breif[in] Getter, Returns a block object from its unique id
        Block getBlockByID(std::string id);
    }

}