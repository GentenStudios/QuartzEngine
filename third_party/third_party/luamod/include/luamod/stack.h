#pragma once

#include <luamod/lua.h>
#include <luamod/table.h>

#include <string>
#include <vector>

namespace lm {
	class Stack;

	class LuaFunction;

	class Stack {
	private:
		lua_State * m_l;
	public:
		Stack(lua_State* state);

		void Push(int n);
		void Push(bool b);
		
		void Push(const char* c);
		void Push(const std::string& str);

		void Push(long l);

		template <typename T, typename... Args>
		void Push(T t, const Args&... args) {
			Push(t);
			Push(args...);
		}

		void Push() {}

		template <typename T>
		T Read(int index=-1);

		template <>
		int Read<int>(int index) {
			int i = lua_tointeger(m_l, index);
			return i;
		}

		template <>
		lua_Number Read<lua_Number>(int index) {
			lua_Number d = lua_tonumber(m_l, index);
			return d;
		}

		template <>
		bool Read<bool>(int index) {
			bool b = lua_toboolean(m_l, index);
			return b;
		}

		template <>
		const char* Read(int index) {
			return lua_tostring(m_l, index);
		}

		template <>
		std::string Read(int index) {
			const char* c = lua_tostring(m_l, index);
			return std::string(c);
		}

		template <typename T>
		T Pop() {
			T top = Read<T>(-1);
			lua_pop(m_l, 1);
			return top;
		}

		template <>
		Table Pop() {
			Table table(m_l);
			table.FromStackTop();
			return table;
		}

		bool TopIsNil() {
			return lua_isnil(m_l, -1);
		}
	};
}
