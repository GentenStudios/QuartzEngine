set(engineHeaders
    ${engineHeaders}
    ${CMAKE_CURRENT_LIST_DIR}/Core.hpp
    ${CMAKE_CURRENT_LIST_DIR}/os.hpp
	${CMAKE_CURRENT_LIST_DIR}/UniversalDoxygenComments.hpp
    CACHE INTERNAL "Global Engine Headers"
)

add_subdirectory(events)
add_subdirectory(graphics)
add_subdirectory(math)
add_subdirectory(utils)
