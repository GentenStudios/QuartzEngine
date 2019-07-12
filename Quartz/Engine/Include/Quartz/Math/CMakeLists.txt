set(currentDir ${CMAKE_CURRENT_LIST_DIR})

set(mathHeaders
	${currentDir}/MathUtils.hpp
	${currentDir}/Matrix4x4.hpp
	${currentDir}/Vector3.hpp
	${currentDir}/Vector2.hpp
	${currentDir}/Ray.hpp
	${currentDir}/Rect.hpp

	${currentDir}/Math.hpp

	PARENT_SCOPE
)
