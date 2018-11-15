set(engineHeaders
    ${engineHeaders}
    include/engine/core/Core.hpp
    include/engine/core/os.hpp
    CACHE INTERNAL "Global Engine Headers"
)

add_subdirectory(events)
add_subdirectory(graphics)
add_subdirectory(math)
add_subdirectory(utils)
