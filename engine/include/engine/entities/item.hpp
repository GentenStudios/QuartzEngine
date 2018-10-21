#pragma once

#include "engine/common.hpp"

#include <string>
#include <vector>

namespace pheonix {

	namespace entities {

		class Item{
        public:
			/**
			 * @brief Initialise an item
			 * @param[in] The unique id for the item, should be in format mod:id to eliminate conflict
			 * @param[in] The player friendly name of the item
			 */
			Item(std::string id, std::string name);
			~Item();

			/**
			 * @brief getID - getID of Item
			 * @return Return a string for the ID of the item
			 */
			std::string getID();

			/**
			 * @brief getName - Get user friendly name of item
			 * @return Return a string of the name of the item
			 */
			std::string getName();

        private:
			/// @brief Unique id using the convention mod:name
			std::string m_id;
			/// @brief Name that will display to the user
			std::string m_name;
        };

        class ItemLibrary
		{
		public:
			/**
			 * @brief getItemByID - Get an item object based off its unique ID
			 * @param[in] The unique ID of the item you are trying to find
			 * @return Returns an item matching the supplied ID
			 */
			static Item getItemByID(std::string id);

			static void registerItem(Item* item);

		private:
			// A registry to keep track of all the registered items
			static std::vector<Item*> m_itemLibrary;
		};
    };
};