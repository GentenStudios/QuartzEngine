cmake_minimum_required(VERSION 3.0)

project(lua)

set(lualib_SRC_CORE
	lapi.c
	lcode.c
	lctype.c
	ldebug.c
	ldo.c
	ldump.c
	lfunc.c
	lgc.c
	llex.c
	lmem.c
	lobject.c
	lopcodes.c
	lparser.c
	lstate.c
	lstring.c
	ltable.c
	ltm.c
	lundump.c
	lvm.c
	lzio.c
)

set(lualib_SRC_LIB
	lauxlib.c
	lbaselib.c
	lbitlib.c
	lcorolib.c
	ldblib.c
	liolib.c
	lmathlib.c
	loslib.c
	lstrlib.c
	ltablib.c
	lutf8lib.c
	loadlib.c
	linit.c
)

set (luacli_SRC lua.c)

add_library(liblua STATIC ${lualib_SRC_CORE} ${lualib_SRC_LIB})
target_include_directories(liblua PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_link_libraries(liblua m)
endif()

set_target_properties (liblua PROPERTIES OUTPUT_NAME lua)

add_executable(lua ${luacli_SRC})
target_link_libraries(lua liblua)
