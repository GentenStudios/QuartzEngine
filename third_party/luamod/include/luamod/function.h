#pragma once

#include <luamod/lua.h>

#include <luamod/argsproxy.h>
#include <luamod/luarefproxy.h>
#include <luamod/returnproxy.h>
#include <luamod/stack.h>
#include <functional>
#include <memory>
#include <typeindex>

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

		template <typename... Args>
		struct ArgsPopper {
			typedef std::tuple<Args...> Type;

			template <typename T>
			static std::tuple<T> DoWork(Stack& s, const int i) {
				return std::make_tuple(s.Read<T>(i));
			}

			template <typename T1, typename T2, typename... Rest>
			static std::tuple<T1, T2, Rest...> DoWork(Stack &s, const int i) {
				std::tuple<T1> head = std::make_tuple(s.Read<T1>(i));
				return std::tuple_cat(head, DoWork<T2, Rest...>(s, i + 1));
			}

			static Type Apply(Stack& s) {
				auto ret = DoWork<Args...>(s, 1);
				lua_pop(s.GetState(), ((int)sizeof...(Args)));
				return ret;
			}
		};

		template<>
		struct ArgsPopper<> {
			static std::tuple<> Apply(Stack& s) { return std::make_tuple<>(); }
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

				std::tuple<Args...> args = ArgsPopper<Args...>::Apply(closureStack);
				RetType t = ArgumentsProxy::Lift(m_func, args);

				detail::Push(state, t);
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

			template <typename... Types>
			void Fill(std::vector<std::type_index>& vec)
			{
				vec.insert(vec.end(), { typeid(Types)... });
			}

			virtual int Call(lua_State* state) {
				Stack closureStack(state);
				
				std::vector<std::type_index> ts;
				Fill<Args...>(ts);
				std::vector<std::string> names;
				for (auto t1 : ts)names.push_back(t1.name());
					
				std::tuple<Args...> args = ArgsPopper<Args...>::Apply(closureStack);
				ArgumentsProxy::Lift(m_func, args);
				return 0;
			}
		};

	}
}