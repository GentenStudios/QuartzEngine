#pragma once

#include <Quartz/Core/Core.hpp>

#include <type_traits>

#define ENABLE_BITMASK_OPERATORS(x)     \
	template<>                          \
	struct EnableBitWiseOperators<x>    \
	{                                   \
	static constexpr bool value = true; \
	};

template<typename Enum>
struct EnableBitWiseOperators
{
	static constexpr bool value = false;
};

namespace qz
{
	template<typename Enum, typename = std::enable_if_t<EnableBitWiseOperators<Enum>::value>>
	bool hasFlag(Enum flags, Enum lookFor)
	{
		using Underlying = std::underlying_type_t<Enum>;
		return static_cast<Underlying>(flags & lookFor);
	}
}

template<typename Enum, typename = std::enable_if_t<::EnableBitWiseOperators<Enum>::value>>
Enum operator |(Enum lhs, Enum rhs)
{
	return static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) |
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);
}

template<typename Enum, typename = std::enable_if_t<::EnableBitWiseOperators<Enum>::value>>
Enum operator &(Enum lhs, Enum rhs)
{
	return static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) &
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);
}

template<typename Enum, typename = std::enable_if_t<EnableBitWiseOperators<Enum>::value>>
Enum operator ^(Enum lhs, Enum rhs)
{
	return static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) ^
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);
}

template<typename Enum, typename = std::enable_if_t<EnableBitWiseOperators<Enum>::value>>
Enum operator ~(Enum rhs)
{
	return static_cast<Enum>(
		~static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);
}

template<typename Enum, typename = std::enable_if_t<EnableBitWiseOperators<Enum>::value>>
Enum& operator |=(Enum& lhs, Enum rhs)
{
	lhs = static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) |
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);

	return lhs;
}

template<typename Enum, typename = std::enable_if_t<EnableBitWiseOperators<Enum>::value>>
Enum& operator &=(Enum& lhs, Enum rhs)
{
	lhs = static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) &
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);

	return lhs;
}

template<typename Enum, typename = std::enable_if_t<EnableBitWiseOperators<Enum>::value>>
Enum& operator ^=(Enum& lhs, Enum rhs)
{
	lhs = static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) ^
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);

	return lhs;
}
