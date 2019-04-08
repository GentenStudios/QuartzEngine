# Copyright (C) 2019 Vyom Fadia
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation files
# (the 'Software') deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Usage:
#	add_library/executable(targetName sources/headers precompiled.hpp precompiled.cpp)
#	add_precompiled_header(targetName precompiled.hpp precompiled.cpp)
#
# - targetName can be whatever you want it to be. 
# 
# - "precompiled.hpp" and "precompiled.cpp" can be named whatever you want as well although 
# 	usually they are named the same thing, for example, the pair are called "stdafx.hpp/cpp"
#	in normal Visual Studio projects.
#
#	THE PATHS MUST BE IN **FULL** (unless in the same directory as the cmake file). The use
#	of ${CMAKE_CURRENT_LIST_DIR} is recommended.

macro(add_precompiled_header target pchHeader pchSource)
	if (MSVC)
		# /Yu is the header to USE.
		# /Yc is the source file used to CREATE the precompiled header.
		# /FI The name of the Forced Include file. This file will be included in EVERY source file.
		set_source_files_properties(${pchSource} PROPERTIES COMPILE_FLAGS "/Yc\"${pchHeader}\"")
		set_target_properties(${target} PROPERTIES COMPILE_FLAGS "/Yu\"${pchHeader}\" /FI\"${pchHeader}\"")
	endif()
endmacro()
