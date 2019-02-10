#pragma once

#include <luamod/lua.h>
#include <luamod/luarefproxy.h>

#include <vector>

namespace lm {
	class Stack;

	/**
	 * Represents the very base type of all lua complex types (e.g. arrays, objects etc...)
	 */
	class TableBase {
	public:
		TableBase(lua_State* state);

		/**
		 * @brief Load this table from a table on the stack.
		 * @param index The index of the table on the stack (in the regular form of lua stack indices).
		 */
		void LoadFromStack(int index);

		/**
		 * @brief Push the lua table onto the stack.
		 */
		void Push();

	protected:
		LuaRefProxy m_ref;
		lua_State*  m_state;
	};

	/**
	 * Represents a lua table - a associative container that forms the basis of all
	 * lua complex types (objects, arrays etc...).
	 *
	 */
	class Table : public TableBase {
	public:
		Table(lua_State* state);
		Table(): TableBase(nullptr) {}

		/**
		 * @brief Get the value a property in this table.
		 * @param propertyName The name of the property.
		 * @param defaultValue If the property does not exist return this value,
		 * @return Either the value of the property (if the property exists) or the specified default value.
		 */
		template <typename T>
		T GetProperty(const char* propertyName, T defaultValue = T()) {
			m_ref.Push();
			lua_getfield(m_state, -1, propertyName);
			
			Stack localStack(m_state);

			if (localStack.TopIsNil())
			{
				lua_pop(m_state, 2);
				return defaultValue;
			}

			T prop = localStack.Pop<T>();
			
			lua_pop(m_state, 1);
			return prop;
		}
	};

	/**
	 * Represents a lua table - an associative container, but in this specific case the keys
	 * are numbers, and act like arrays.
	 *
	 * Note: Lua arrays are 1-indexed (e.g. start from 1 and not zero) and that applies also for this Array abstraction - e.g.
	 * for the At method. Does not apply to any other arrays, e.g. the vector returned by ToVector are still 0-indexed.
	 */
	class Array : public TableBase {
	public:
		Array(lua_State* state);
		Array(): TableBase(nullptr) {}

		/**
		 * @brief Get the number of elements in this array.
		 * @return The number of elements in this array
		 */
		int Count();
		
		/**
		 * @brief Convert this array to a std::vector<T>. Requires that all values in the lua array are of the same type.
		 * @return A std::vector<T> that contains a copy of all the values in this array.
		 */
		template <typename T>
		std::vector<T> ToVector() {
			const int count = Count();

			std::vector<T> vector;
			for (int i = 1; i <= count; i++) {
				vector.push_back(At<T>(i));
			}

			return vector;
		}

		/**
		 * @brief Get the element in the array at the given index.
		 *        Indices are 1-indexed - e.g. to get the first element in the array, call At(1)
		 * @param index The index of the element. 1-indexed (e.g. starts from 1 and not zero).
		 * @return A copy of the element in the array at the given index.
		 */
		template <typename T>
		T At(int index) {
			assert(index > 0);
			assert(index <= Count());
			
			m_ref.Push();
			lua_pushnumber(m_state, index);
			lua_gettable(m_state, -2);

			Stack localStack(m_state);
			
			if (localStack.TopIsNil()) {
				lua_pop(m_state, 2);
				return T();
			}

			T out = localStack.Pop<T>();
			lua_pop(m_state, 1);

			return out;
		}
	};
}
