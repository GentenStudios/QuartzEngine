set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(mathSources
	${currentDir}/Vector2.cpp
	${currentDir}/Vector3.cpp
	${currentDir}/Matrix4x4.cpp
	${currentDir}/Ray.cpp

	PARENT_SCOPE
)
