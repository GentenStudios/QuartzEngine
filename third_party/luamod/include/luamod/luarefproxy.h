#pragma once

#include <luamod/lua.h>

#include <assert.h>
#include <memory>

namespace lm {
	/**
	 * Represents a lua reference - stores a reference to a lua object that can be then used from C/C++.
	 * aka basically pointers to lua objects (sort of).
	 * See https://www.lua.org/pil/27.3.2.html
	 */
	class LuaRefProxy {
	public:
		typedef int RefID;

		LuaRefProxy(lua_State* state);
		LuaRefProxy() {}

		/**
		 * @brief Get the internal Lua reference number.
		 * @return The internal Lua reference index.
		 */
		inline RefID GetRef() const { return *m_refindex; }

		/**
		 * @brief Create a stored reference to the item currently on the lua stack at index i.
		 * @param i The index of the element on the stack. Act's like any other lua stack index (e.g. -1 refers to top, -2 the one below etc...)
		 */
		void CreateFromStack(int i);

		/**
		 * @brief Push the value of this reference to the Lua stack.
		 */
		void Push();

	private:
		std::shared_ptr<RefID> m_refindex;
		lua_State* m_state;
		bool m_inUse;
	};
}
