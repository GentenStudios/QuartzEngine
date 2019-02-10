#include <luamod/luastate.h>

using namespace lm;

LuaState::LuaState() {
	m_state = lua_open();
	luaL_openlibs(m_state);

	m_stack = std::unique_ptr<Stack>(new Stack(m_state));
}

LuaState::~LuaState() {
	lua_close(m_state);
}
