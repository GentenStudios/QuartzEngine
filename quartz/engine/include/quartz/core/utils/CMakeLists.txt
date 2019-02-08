set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(utilHeaders
    ${currentDir}/IO.hpp
    ${currentDir}/Logging.hpp
    ${currentDir}/Config.hpp
    ${currentDir}/ThreadPool.hpp

	PARENT_SCOPE
)