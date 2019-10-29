add_subdirectory(Threading)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(utilityHeaders
	${threadingHeaders}

	${currentDir}/Logger.hpp
	${currentDir}/FileIO.hpp
	${currentDir}/HandleAllocator.hpp
	${currentDir}/EnumTools.hpp
	${currentDir}/Singleton.hpp
	${currentDir}/Plugin.hpp
	
	PARENT_SCOPE
)
