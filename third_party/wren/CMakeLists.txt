cmake_minimum_required( VERSION 3.0 )

project( WrenVM )

set( VM_DIR ${CMAKE_CURRENT_LIST_DIR}/src/vm )

# Create a list of required source files
set(WREN_VM_SOURCES
    ${VM_DIR}/wren_compiler.c
    ${VM_DIR}/wren_core.c
    ${VM_DIR}/wren_debug.c
    ${VM_DIR}/wren_primitive.c
    ${VM_DIR}/wren_utils.c
    ${VM_DIR}/wren_value.c
    ${VM_DIR}/wren_vm.c
    src/optional/wren_opt_meta.c
    src/optional/wren_opt_random.c
    )

# Create a list of headers required.
set(WREN_VM_HEADERS
    src/include/wren.h
    src/include/wren.hpp
    src/optional/wren_opt_meta.h
    src/optional/wren_opt_random.h
    ${VM_DIR}/wren_common.h
    ${VM_DIR}/wren_compiler.h
    ${VM_DIR}/wren_core.h
    ${VM_DIR}/wren_debug.h
    ${VM_DIR}/wren_opcodes.h
    ${VM_DIR}/wren_primitive.h
    ${VM_DIR}/wren_utils.h
    ${VM_DIR}/wren_value.h
    ${VM_DIR}/wren_vm.h
    )

# Add VM, generic & optional folders as include directories
include_directories( src/vm )
include_directories( src/include )
include_directories( src/optional )

# Add library, to make files compile into a static library
add_library( ${PROJECT_NAME} STATIC ${WREN_VM_SOURCES} ${WREN_VM_INCLUDES} )

