set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(utilityHeaders
	${currentDir}/Logger.hpp
	${currentDir}/FileIO.hpp
	${currentDir}/Config.hpp
	${currentDir}/ThreadPool.hpp
	${currentDir}/HandleAllocator.hpp
	
	PARENT_SCOPE
)
