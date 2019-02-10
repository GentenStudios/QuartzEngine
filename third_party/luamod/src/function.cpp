#include <luamod/function.h>

using namespace lm;

int detail::LuaFunctorDispatch(lua_State* state) {
	detail::CFunctionProxyBase* func = (detail::CFunctionProxyBase*)lua_touserdata(state, lua_upvalueindex(1));
	int nresults = func->Call(state);
	return nresults;
}
