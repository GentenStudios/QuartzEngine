#include <luamod/stack.h>

using namespace lm;

Stack::Stack(lua_State* state)
	: m_l(state) {}

void Stack::Push(int n) {
	lua_pushinteger(m_l, n);
}

void Stack::Push(bool b) {
	lua_pushboolean(m_l, b);
}

void Stack::Push(const char* c) {
	lua_pushstring(m_l, c);
}

void Stack::Push(const std::string& str) {
	lua_pushstring(m_l, str.c_str());
}

void Stack::Push(long l) {
	lua_pushinteger(m_l, static_cast<lua_Integer>(l));
}