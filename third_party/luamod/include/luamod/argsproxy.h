#pragma once

#include <functional>
#include <tuple>

namespace lm {
	class Stack;

	namespace detail {
		/*
			This useful method for unpack a tuple into a functions parameter pack I got from
			https://www.jeremyong.com/lua/c++11/templates/metaprogramming/2014/01/15/interfacing-lua-with-templates-in-c-plus-plus-11-continued.html
		*/
		template <std::size_t... Is>
		struct Indices {};

		template <std::size_t N, std::size_t... Is>
		struct IndicesBuilder : IndicesBuilder<N - 1, N - 1, Is...> {};

		template <std::size_t... Is>
		struct IndicesBuilder<0, Is...> {
			typedef Indices<Is...> type;
		};

		struct ArgumentsProxy {
			template <typename Ret, typename... Args, std::size_t... N>
			static Ret Lift(std::function<Ret(Args...)> fun,
				std::tuple<Args...> args,
				Indices<N...>) {
				return fun(std::get<N>(args)...);
			}

			template <typename Ret, typename... Args>
			static Ret Lift(std::function<Ret(Args...)> fun,
				std::tuple<Args...> args) {
				return Lift(fun, args, typename IndicesBuilder<sizeof...(Args)>::type());
			}
		};


	}
}