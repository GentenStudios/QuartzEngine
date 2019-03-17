set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(threadingSources
	${currentDir}/SingleWorker.cpp
	${currentDir}/ThreadPool.cpp
	
	PARENT_SCOPE
)
