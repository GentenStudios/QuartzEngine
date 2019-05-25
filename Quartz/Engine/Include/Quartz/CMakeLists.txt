add_subdirectory(Core)
add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Graphics)

set(coreHeaderSystem
	${coreHeaders}
	${voxelHeaders}

	${graphicsHeaders}
	${mathHeaders}

	PARENT_SCOPE
)
