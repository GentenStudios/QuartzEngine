#include <luamod/table.h>

#include <assert.h>

using namespace lm;

TableBase::TableBase(lua_State* state)
	: m_state(state){}

void TableBase::Push() {
	m_ref.Push();
}

void TableBase::LoadFromStack(int index) {
	m_ref = LuaRefProxy(m_state);
	m_ref.CreateFromStack(index);
}

Table::Table(lua_State* state) 
	: TableBase(state) { }

Array::Array(lua_State* state)
	: TableBase(state) { }

int Array::Count() {
	m_ref.Push();
	lua_len(m_state, -1);
	
	int count = static_cast<int>(lua_tonumber(m_state, -1));

	lua_pop(m_state, 1);
	return count;
}