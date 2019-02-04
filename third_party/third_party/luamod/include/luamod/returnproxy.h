#pragma once

#include <luamod/stack.h>

#include <memory>

namespace lm {
	namespace detail {
		template <int, typename... T1>
		struct ReturnProxy {
		};

		template <typename T1>
		struct ReturnProxy<1, T1> {
			typedef T1 type;

			static T1 Pop(Stack& stack) {
				return stack.Pop<T1>();
			}
		};

		template <typename... Ts>
		struct ReturnProxy<0, Ts...> {
			typedef void type;

			static void Pop(Stack& stack) {}
		};
	}
}