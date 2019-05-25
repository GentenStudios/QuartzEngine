add_subdirectory(GL)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(apiHeaders
	${currentDir}/Context.hpp
	${currentDir}/InputLayout.hpp
	${currentDir}/DataTypes.hpp
	${currentDir}/IRenderDevice.hpp

	${glAPIHeaders}

	PARENT_SCOPE
)
