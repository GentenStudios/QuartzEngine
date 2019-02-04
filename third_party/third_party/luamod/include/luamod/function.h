#pragma once

#include <luamod/lua.h>

#include <luamod/argsproxy.h>
#include <luamod/luarefproxy.h>
#include <luamod/returnproxy.h>
#include <luamod/stack.h>
#include <functional>
#include <memory>

namespace lm {
	class Stack;

	namespace detail {
		class CFunctionProxyBase {
		public:
			virtual int Call(lua_State* state) = 0;
		};

		int LuaFunctorDispatch(lua_State* state);

		template <typename T>
		struct LambdaTraits : public LambdaTraits<decltype(&T::operator())> {};

		template <typename T, typename RetType, typename... Args>
		struct LambdaTraits<RetType(T::*)(Args...) const> {
			typedef std::function<RetType(Args...)> Functor;
		};

		template <typename... Args>
		struct VaradicPack {};

		template <typename T>
		struct FunctorTraits {};

		template <typename Ret, typename... Args>
		struct FunctorTraits<Ret(Args...)> {
			typedef Ret ReturnType;
			using Arguments = VaradicPack<Args...>;
		};

		template <typename RetType, typename... Args>
		class CFunctionProxy : public CFunctionProxyBase {
		private:
			typedef std::function<RetType(Args...)> FuncSig;
			FuncSig m_func;

		public:
			CFunctionProxy(lua_State* l, const char* name, FuncSig func)
				: m_func(func) {
				lua_pushlightuserdata(l, (void*)static_cast<CFunctionProxyBase*>(this));
				lua_pushcclosure(l, &LuaFunctorDispatch, 1);
				lua_setglobal(l, name);
			}

			virtual int Call(lua_State* state) {
				Stack closureStack(state);
				
				std::tuple<Args...> args = std::make_tuple(closureStack.Pop<Args>()...);
				RetType t = ArgumentsProxy::Lift(m_func, args);

				closureStack.Push(t);
				return 1;
			}
		};

		template <typename... Args>
		class CFunctionProxy<void, Args...> : public CFunctionProxyBase {
		private:
			typedef std::function<void(Args...)> FuncSig;
			FuncSig m_func;

		public:
			CFunctionProxy(lua_State* l, const char* name, FuncSig func)
				: m_func(func) {
				lua_pushlightuserdata(l, (void*)static_cast<CFunctionProxyBase*>(this));
				lua_pushcclosure(l, &LuaFunctorDispatch, 1);
				lua_setglobal(l, name);
			}

			virtual int Call(lua_State* state) {
				Stack closureStack(state);
				std::tuple<Args...> args = std::make_tuple(closureStack.Pop<Args>()...);
				ArgumentsProxy::Lift(m_func, args);
				return 0;
			}
		};

	}
	
	class LuaFunction {
	public:
		LuaFunction(lua_State* state) : m_state(state) {}
		LuaFunction() {}

		void FromStackTop() {
			m_ref = LuaRefProxy(m_state);
			m_ref.CreateFromStackTop();
		}

		void operator()() {
			m_ref.Push();
			lua_pcall(m_state, 0, LUA_MULTRET, 0);
			lua_pop(m_state, 1);
		}

	private:
		LuaRefProxy m_ref;
		lua_State* m_state;
	};
}