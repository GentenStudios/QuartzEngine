set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(eventHeaders
	${currentDir}/Event.hpp
	${currentDir}/KeyEvent.hpp
	${currentDir}/MouseEvent.hpp
	${currentDir}/ApplicationEvent.hpp
	${currentDir}/EventEnums.hpp
	
	PARENT_SCOPE
)
