// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#pragma once

#include <Quartz/Core/Internals/QuartzDefines.hpp>

#include <cstdint>

using int8   = std::int8_t;
using uint8  = std::uint8_t;
using int16  = std::int16_t;
using uint16 = std::uint16_t;
using int32  = std::int32_t;
using uint32 = std::uint32_t;
using int64  = std::int64_t;
using uint64 = std::uint64_t;

using byte = uint8;

using uint = uint32;

// Makes sure everything is the right size and compilers haven't messed it all up (highly unlikely but still)
static_assert(sizeof(uint64) == 8, "Custom aliased type \'uint64\' is not of size 8 bytes!");
static_assert(sizeof(uint32) == 4, "Custom aliased type \'uint64\' is not of size 8 bytes!");
static_assert(sizeof(uint16) == 2, "Custom aliased type \'uint64\' is not of size 8 bytes!");
static_assert(sizeof(uint8) == 1, "Custom aliased type \'uint8\'  is not of size 1 bytes!");
static_assert(sizeof(byte) == 1, "Custom aliased type \'byte\'  is not of size 1 bytes!");

static_assert(sizeof(int64) == 8, "Custom aliased type \'int64\' is not of size 8 bytes!");
static_assert(sizeof(int32) == 4, "Custom aliased type \'int32\' is not of size 8 bytes!");
static_assert(sizeof(int16) == 2, "Custom aliased type \'int16\' is not of size 8 bytes!");
static_assert(sizeof(int8) == 1, "Custom aliased type \'int8\'  is not of size 1 bytes!");
