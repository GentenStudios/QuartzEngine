add_subdirectory(Threading)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(utilityHeaders
	${threadingHeaders}

	${currentDir}/Logger.hpp
	${currentDir}/FileIO.hpp
	${currentDir}/HandleAllocator.hpp
	${currentDir}/EnumTools.hpp
	${currentDir}/Singleton.hpp
<<<<<<< HEAD
	${currentDir}/Commander.hpp
=======
	${currentDir}/Plugin.hpp
>>>>>>> c177f7330a770193eec5e027f27b5a3359600bcb
	
	PARENT_SCOPE
)
