set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(mathHeaders
	${currentDir}/Vector2.hpp
	${currentDir}/Vector3.hpp
	${currentDir}/Matrix4x4.hpp
	${currentDir}/MathUtils.hpp
	${currentDir}/Ray.hpp

	PARENT_SCOPE
)
