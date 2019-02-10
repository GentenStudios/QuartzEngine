#pragma once

#include <luamod/lua.h>
#include <luamod/table.h>

#include <string>
#include <vector>

namespace lm {
	namespace detail {
		void Push(lua_State* l, int n);
		void Push(lua_State* l, bool b);

		void Push(lua_State* l, const char* c);
		void Push(lua_State* l, const std::string& str);

		void Push(lua_State* l, long l2);

		template <typename T, typename... Args>
		void Push(lua_State* l, T t, const Args&... args) {
			Push(t);
			Push(args...);
		}

		void Push();
	}

	class Stack {
	private:
		lua_State * m_l;
	public:
		Stack(lua_State* state);

		template <typename T>
		T Read(int index =- 1);

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
		const char* Read<const char*>(int index) {
			const char* c = lua_tostring(m_l, index);
			return c;
		}

		template <>
		std::string Read<std::string>(int index) {
			const char* c = lua_tostring(m_l, index);
			return std::string(c);
		}

		template <>
		Array Read(int index) {
			Array array(m_l);
			array.LoadFromStack(index);
			array.Push();
			return array;
		}

		template <>
		Table Read(int index) {
			Table table(m_l);
			table.LoadFromStack(index);
			table.Push();
			return table;
		}

		lua_State* GetState() {
			return m_l;
		}

		template <typename T>
		T Pop() {
			T top = Read<T>(-1);
			lua_pop(m_l, 1);
			return top;
		}

		bool TopIsNil() {
			return lua_isnil(m_l, -1);
		}
	};
}
