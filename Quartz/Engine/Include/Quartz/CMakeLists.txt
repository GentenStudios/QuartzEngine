add_subdirectory(Core)
# add_subdirectory(Voxels)

set(coreHeaderSystem
	${coreHeaders}
	${voxelHeaders}

	PARENT_SCOPE
)
