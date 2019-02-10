#pragma once

#include <luamod/lua.h>
#include <luamod/stack.h>
#include <luamod/returnproxy.h>
#include <luamod/function.h>

#include <memory>
#include <functional>

namespace lm {

	class LuaState {
	private:
		lua_State * m_state;
		std::unique_ptr<Stack> m_stack;

	public:
		LuaState();
		~LuaState();

		/**
		 * @brief Load and then run a Lua script.
		 * @param filepath The filepath to the Lua script to run.
		 */
		template <typename... ReturnType>
		typename detail::ReturnProxy<sizeof...(ReturnType), ReturnType...>::type RunFile(const char* filepath) {
			luaL_loadfile(m_state, filepath);
			lua_pcall(m_state, 0, LUA_MULTRET, 0);

			return detail::ReturnProxy<sizeof...(ReturnType), ReturnType...>::Pop(*m_stack);
		}
		
		/**
		 * @brief Get the Lua stack abstraction that belongs to this state. DO NOT delete this pointer.
		 * @return A pointer to the Lua stack for this state.
		 */
		inline Stack* GetStack() { return m_stack.get(); }

		/**
		 * @brief Get the internal lua_State* object.
		 * @return The internal lua_State* used by this state.
		 */
		inline lua_State* GetLuaState() { return m_state; }


		/**
		 * @brief Register a std::function<...> object with this Lua state.
		 * @param funcName The name of the function as it will appear in Lua. 
		 * @param func The function object to bind.
		 */
		template <typename RetType, typename... Args>
		void Register(const char* funcName, std::function<RetType(Args...)> func) {
			new detail::CFunctionProxy<RetType, Args...>(m_state, funcName, func);
		}


		/**
		 * @brief Register a function pointer with this Lua state.
		 * @param funcName The name of the function as it will appear in Lua.
		 * @param func The function pointer to bind.
		 */
		template <typename RetType, typename... Args>
		void Register(const char* funcName, RetType(*func)(Args...)) {
			new detail::CFunctionProxy<RetType, Args...>(m_state, funcName, std::function<RetType(Args...)>(func));
		}

		/**
		 * @brief Register a lambda function with this Lua state.
		 * @param funcName The name of the function as it will appear in Lua.
		 * @param lambda The lambda to bind.
		 */
		template <typename LambdaType>
		void Register(const char* funcName, LambdaType lambda) {
			Register(funcName, (typename detail::LambdaTraits<LambdaType>::Functor)(lambda));
		}


		/**
		 * @brief Get the value of a global variable (that has specified type T) from inside Lua.
		 * @param globalName The name of the Lua global variable.
		 * @return The value of the lua global variable.
		 */
		template <typename T>
		T GetGlobal(const char* globalName) {
			lua_getglobal(m_state, globalName);
			T global = m_stack->Pop<T>();
			return global;
		}


		/**
		 * @brief Set the value of a global variable (that has specified type T) inside Lua.
		 * @param globalName The name of the Lua global variable.
		 * @param value The value to set the Lua global to.
		 */
		template <typename T>
		void SetGlobal(const char* globalName, const T& value) {
			detail::Push(m_state, value);
			lua_setglobal(m_state, globalName);
		}


		/**
		 * @brief Call a Lua function from C++.
		 * @param funcName The name of the Lua function to call.
		 * @param args The arguments to pass to the Lua function.
		 * @return The value returned by the called Lua function.
		 */
		template <typename... RetType, typename... Args>
		typename detail::ReturnProxy<sizeof...(RetType), RetType...>::type Call(const char* funcName, const Args&... args) {
			lua_getglobal(m_state, funcName);
			detail::Push(m_state, args...);
			
			lua_pcall(m_state, sizeof...(args), sizeof...(RetType), 0);

			return detail::ReturnProxy<sizeof...(RetType), RetType...>::Pop(*m_stack);
		}
	};
}