add_subdirectory(Threading)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(utilityHeaders
	${threadingHeaders}

	${currentDir}/Logger.hpp
	${currentDir}/FileIO.hpp
	${currentDir}/Config.hpp
	${currentDir}/HandleAllocator.hpp
	${currentDir}/Singleton.hpp
	
	PARENT_SCOPE
)
