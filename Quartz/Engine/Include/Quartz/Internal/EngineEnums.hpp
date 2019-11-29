#pragma once

#include <type_traits>

#define ENABLE_BITWISE_OPERATORS(x)     \
	template<>                          \
	struct EnableBitWiseOperators<x>    \
	{                                   \
	static constexpr bool value = true; \
	}

template<typename Enum>
struct EnableBitWiseOperators
{
	static constexpr bool value = false;
};

template<typename Enum, typename = typename std::enable_if<EnableBitWiseOperators<Enum>::value>::type>
Enum operator |(Enum lhs, Enum rhs)
{
	return static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) |
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);
}

template<typename Enum, typename = typename std::enable_if<EnableBitWiseOperators<Enum>::value>::type>
Enum operator &(Enum lhs, Enum rhs)
{
	return static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) &
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);
}

template<typename Enum, typename = typename std::enable_if<EnableBitWiseOperators<Enum>::value>::type>
Enum operator ^(Enum lhs, Enum rhs)
{
	return static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) ^
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);
}

template<typename Enum, typename = typename std::enable_if<EnableBitWiseOperators<Enum>::value>::type>
Enum operator ~(Enum rhs)
{
	return static_cast<Enum>(
		~static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);
}

template<typename Enum, typename = typename std::enable_if<EnableBitWiseOperators<Enum>::value>::type>
Enum & operator |=(Enum & lhs, Enum rhs)
{
	lhs = static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) |
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);

	return lhs;
}

template<typename Enum, typename = typename std::enable_if<EnableBitWiseOperators<Enum>::value>::type>
Enum & operator &=(Enum & lhs, Enum rhs)
{
	lhs = static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) &
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);

	return lhs;
}

template<typename Enum, typename = typename std::enable_if<EnableBitWiseOperators<Enum>::value>::type>
Enum & operator ^=(Enum & lhs, Enum rhs)
{
	lhs = static_cast<Enum>(
		static_cast<typename std::underlying_type<Enum>::type>(lhs) ^
		static_cast<typename std::underlying_type<Enum>::type>(rhs)
		);

	return lhs;
}

namespace qz
{
	template<typename Enum, typename = typename std::enable_if<EnableBitWiseOperators<Enum>::value>::type>
	bool ENUMhasFlag(Enum flags, Enum lookFor)
	{
		return static_cast<typename std::underlying_type<Enum>::type>(flags & lookFor);
	}
}
