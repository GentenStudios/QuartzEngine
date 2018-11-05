#pragma once

#include "engine/common.hpp"

#include <functional>

namespace phx
{
	namespace voxels
	{
		/// @brief This defines what state of matter the block is
		enum class BlockType
		{
			GAS,    ///< Gas Blocks are, for example, Air, or Oxygen if implemented.
			LIQUID, ///< Fluid Liquid Dynamics are applied to these blocks.
			SOLID,  ///< Generic Stable Block, used for most things.
			WATER, ///< Water as a fundamental type as it needs to be specially done.
			OBJECT, ///< Things like Entities and objects that like transparent turds.
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
			Block(const Block& other);
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

			/////////////////////////////////////////////
			// Getters and setters for event callbacks //
			/////////////////////////////////////////////

			/// @brief Setter: Sets the function executed when a block is placed
			void setOnPlaceCallback(std::function<void()> callback);
			/// @brief Getter: Gets the function executed when a block is placed
			std::function<void()> getOnPlaceCallback();

			/// @brief Setter: Sets the function executed when a block is broken
			void setOnBreakCallback(std::function<void()> callback);
			/// @brief Getter: Gets the function executed when a block is broken
			std::function<void()> getOnBreakCallback();

			/// @brief Setter: Sets the function executed when a block is left clicked
			void setOnInteractLeftCallback(std::function<void()> callback);
			/// @brief Getter: Gets the function executed when a block is left clicked
			std::function<void()> getOnInteractLeftCallback();

			/// @brief Setter: Sets the function executed when a block is right clicked
			void setOnInteractRightCallback(std::function<void()> callback);
			/// @brief Getter: Gets the function executed when a block is right clicked
			std::function<void()> getOnInteractRightCallback();

		private:
			/// @brief Unique id using the convention mod:name
			std::string m_id;
			/// @brief Name that will display to the user
			std::string m_name;
			/// @brief State of matter of the block
			BlockType m_blockType;
			//  ??????? m_textures; //String? Array of strings? Array of file pointers? Image class?

			/// @brief Lambda callback for when the block is placed (well, hopefully lambdas if we can)
			std::function<void()> m_onPlaceCallback;
			/// @brief Lambda callback for when the block is broken (well, hopefully lambdas if we can)
			std::function<void()> m_onBreakCallback;
			/// @brief Lambda callback for when the block is interacted with by left arm (well, hopefully lambdas if we can)
			std::function<void()> m_onInteractLeftCallback;
			/// @brief Lambda callback for when the block is interacted with by right arm (well, hopefully lambdas if we can)
			std::function<void()> m_onInteractRightCallback;
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
			/// @brief A registry to keep track of all the registered blocks
			static std::vector<Block*> m_blockLibrary;
		};
	}
}