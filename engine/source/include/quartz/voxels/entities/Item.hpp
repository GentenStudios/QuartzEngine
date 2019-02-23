// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#pragma once

#include <quartz/core/Core.hpp>

#include <string>
#include <vector>

namespace qz
{
	namespace entities
	{
		class Item
		{
		public:
			/**
			 * @brief Initialise an item
			 * @param The unique id for the item, should be in format mod:id to eliminate conflict
			 * @param The player friendly name of the item
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

			/// @brief Setter: Sets the function executed when an items breaks (damage used up)
			void setOnBreakCallback(void* callback);
			/// @brief Getter: Gets the function executed when an item breaks (damage used up)
			void* getOnBreakCallback();

			/// @brief Setter: Sets the function executed when you use the item
			void setOnUseCallback(void* callback);
			/// @brief Getter: Gets the function executed when you use the item
			void* getOnUseCallback();

		private:
			/// @brief Unique id using the convention mod:name
			std::string m_id;
			/// @brief Name that will display to the user
			std::string m_name;

			/// @brief Lambda callback for when the item is broken (well, hopefully lambdas if we can)
			void* m_onBreakCallback;
			/// @brief Lambda callback for when the item is used (well, hopefully lambdas if we can)
			void* m_onUseCallback;
		};

		class ItemLibrary
		{
		public:
			/**
			 * @brief getItemByID - Get an item object based off its unique ID
			 * @param The unique ID of the item you are trying to find
			 * @return Returns an item matching the supplied ID
			 */
			static Item getItemByID(std::string id);

			static void registerItem(Item* item);

		private:
			// A registry to keep track of all the registered items
			static std::vector<Item*> m_itemLibrary;
		};
	}
}
