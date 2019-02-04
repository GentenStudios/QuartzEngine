#pragma once

#include <luamod/lua.h>
#include <assert.h>
#include <memory>

namespace lm {
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
		 * @brief Make this act as a reference to the item on top of the Lua stack (at the time of calling).
		 */
		void CreateFromStackTop();
		
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
