// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

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

