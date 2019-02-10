#pragma once

extern "C" {
#include "../vendor/luajit/src/lua.h"
#include "../vendor/luajit/src/lauxlib.h"
#include "../vendor/luajit/src/lualib.h"
#include "../vendor/luajit/src/luajit.h"
}

static void lua_len(lua_State *L, int i) {
	switch (lua_type(L, i)) {
	case LUA_TSTRING:
		lua_pushnumber(L, (lua_Number)lua_objlen(L, i));
		break;
	case LUA_TTABLE:
		if (!luaL_callmeta(L, i, "__len"))
			lua_pushnumber(L, (lua_Number)lua_objlen(L, i));
		break;
	case LUA_TUSERDATA:
		if (luaL_callmeta(L, i, "__len"))
			break;
		/* FALLTHROUGH */
	default:
		luaL_error(L, "attempt to get length of a %s value",
			lua_typename(L, lua_type(L, i)));
	}
}