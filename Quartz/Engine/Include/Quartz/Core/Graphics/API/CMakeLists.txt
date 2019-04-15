add_subdirectory(GL)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(apiHeaders
	${currentDir}/InputLayout.hpp
	${currentDir}/GFXTypes.hpp
	${currentDir}/IRenderDevice.hpp

	${glAPIHeaders}

	PARENT_SCOPE
)
