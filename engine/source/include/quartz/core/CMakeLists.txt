add_subdirectory(events)
add_subdirectory(graphics)
add_subdirectory(math)
add_subdirectory(utils)
add_subdirectory(platform)

set(coreHeaders
    ${eventHeaders}
    ${graphicsHeaders}
    ${mathHeaders}
    ${utilHeaders}
    ${platformHeaders}

    ${CMAKE_CURRENT_LIST_DIR}/Core.hpp
    ${CMAKE_CURRENT_LIST_DIR}/UniversalDoxygenComments.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Application.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EntryPoint.hpp
    ${CMAKE_CURRENT_LIST_DIR}/quartz-pch.hpp

    PARENT_SCOPE
)