add_subdirectory(Core)
add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Graphics)
add_subdirectory(Utilities)

set(coreHeaderSystem
	${coreHeaders}
	${voxelHeaders}

	${graphicsHeaders}
	${mathHeaders}
	${utilityHeaders}

	PARENT_SCOPE
)
