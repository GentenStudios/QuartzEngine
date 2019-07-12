set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(threadingHeaders
	${currentDir}/SingleWorker.hpp
	${currentDir}/ThreadPool.hpp
	
	PARENT_SCOPE
)
