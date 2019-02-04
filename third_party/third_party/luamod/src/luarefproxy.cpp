#include <luamod/luarefproxy.h>
#include <stdio.h>
using namespace lm;

namespace detail {
	struct LuaRefProxyDeleter {
	private:
		lua_State *m_l;

	public:
		LuaRefProxyDeleter(lua_State* l)
			: m_l(l) {
		}

		void operator()(int *ref) {
			lua_unref(m_l, *ref);
			delete ref;
		}
	};
} 

LuaRefProxy::LuaRefProxy(lua_State* state)
	: m_state(state), m_inUse(false) {}

void LuaRefProxy::CreateFromStackTop() {
	assert(!m_inUse);
	
	RefID ref = lua_ref(m_state, true);
	m_refindex = std::shared_ptr<RefID>(new RefID{ ref }, detail::LuaRefProxyDeleter{m_state});

	m_inUse = true;
}

void LuaRefProxy::Push() {
	lua_getref(m_state, GetRef());
}
