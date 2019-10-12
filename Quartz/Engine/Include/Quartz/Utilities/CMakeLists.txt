add_subdirectory(Threading)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(utilityHeaders
	${threadingHeaders}

	${currentDir}/Logger.hpp
	${currentDir}/FileIO.hpp
	${currentDir}/Config.hpp
	${currentDir}/HandleAllocator.hpp
	${currentDir}/EnumTools.hpp
	${currentDir}/Singleton.hpp
	${currentDir}/Commander.hpp
	
	PARENT_SCOPE
)
