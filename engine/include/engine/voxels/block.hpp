#pragma once

#include "engine/common.hpp"

#include <string>
#include <vector>

namespace phoenix {

	namespace voxels {
		
		enum class BlockFace
		{
			FRONT,
			BACK,
			RIGHT,
			LEFT,
			BOTTOM,
			TOP
		};

		/// @brief This defines what state of matter the block is
		enum class BlockType
		{
			GAS,    ///< Gas Blocks are, for example, Air, or Oxygen if implemented.
			LIQUID, ///< Fluid Liquid Dynamics are applied to these blocks.
			SOLID   ///< Generic Stable Block, used for most things.
		};

		class Block
		{
		public:
			/**
			 * @brief Initialise a block
			 * @param[in] The unique id for the block, should be in format mod:id to eliminate conflict
			 * @param[in] The player friendly name of the block
			 * @param[in] The block type (SOLID, LIQUID, GAS)
			 */
			Block(std::string id, std::string name, BlockType type);
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

			/**
			 * @brief getBlockType - Get the matter state type of the block
			 * @return Return the state of matter the block is
			 */
			BlockType getBlockType();

			//  ??????? getTextures();

		private:
			/// @brief Unique id using the convention mod:name
			std::string m_id;
			/// @brief Name that will display to the user
			std::string m_name;
			/// @brief Short description of the block
			BlockType m_blockType;
			//  ??????? m_textures; //String? Array of strings? Array of file pointers? Image class?
		};

		class BlockLibrary
		{
		public:
			/**
			 * @brief getBlockByID - Get a block object based off its unique ID
			 * @param[in] The unique ID of the block you are trying to find
			 * @return Returns a Block matching the supplied ID
			 */
			static Block getBlockByID(std::string id);

			static void registerBlock(Block* block);

		private:
			// A registry to keep track of all the registered blocks
			static std::vector<Block*> m_blockLibrary;

		};

	}

}
