add_subdirectory(Threading)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(utilitySources
	${threadingSources}

	${currentDir}/Logger.cpp
	${currentDir}/FileIO.cpp
	${currentDir}/Plugin.cpp
	${currentDir}/ContentLoader.cpp

	PARENT_SCOPE
)
