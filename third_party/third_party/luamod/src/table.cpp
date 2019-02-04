#include <luamod/table.h>
#include <assert.h>

using namespace lm;

Table::Table(lua_State* state) 
	: m_state(state) {
}

void Table::FromStackTop() {
	m_ref = LuaRefProxy(m_state);
	m_ref.CreateFromStackTop();
}