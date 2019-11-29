#pragma once

#include <cstdint>

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using byte = std::uint8_t;
using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint = uint32;
using uint64 = std::uint64_t;

// Makes sure everything is the right size and compilers haven't messed it all up (highly unlikely but still)
static_assert(sizeof(uint64) == 8, "Custom aliased type \'uint64\' is not of size 8 bytes!");
static_assert(sizeof(uint32) == 4, "Custom aliased type \'uint64\' is not of size 8 bytes!");
static_assert(sizeof(uint16) == 2, "Custom aliased type \'uint64\' is not of size 8 bytes!");
static_assert(sizeof(uint8) == 1, "Custom aliased type \'uint8\'  is not of size 1 bytes!");

static_assert(sizeof(int64) == 8, "Custom aliased type \'int64\' is not of size 8 bytes!");
static_assert(sizeof(int32) == 4, "Custom aliased type \'int32\' is not of size 8 bytes!");
static_assert(sizeof(int16) == 2, "Custom aliased type \'int16\' is not of size 8 bytes!");
static_assert(sizeof(int8) == 1, "Custom aliased type \'int8\'  is not of size 1 bytes!");
