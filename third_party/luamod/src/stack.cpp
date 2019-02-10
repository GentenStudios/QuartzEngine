#include <luamod/stack.h>

using namespace lm;

Stack::Stack(lua_State* state)
	: m_l(state) {}

void detail::Push(lua_State* l, int n) {
	lua_pushinteger(l, n);
}

void detail::Push(lua_State* l, bool b) {
	lua_pushboolean(l, b);
}

void detail::Push(lua_State* l, const char* c) {
	lua_pushstring(l, c);
}

void detail::Push(lua_State* l, const std::string& str) {
	lua_pushstring(l, str.c_str());
}

void detail::Push(lua_State* l, long l2) {
	lua_pushinteger(l, static_cast<lua_Integer>(l2));
}

void detail::Push(){}