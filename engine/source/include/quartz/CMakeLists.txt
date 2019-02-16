add_subdirectory(core)
# add_subdirectory(voxels)

set(coreHeaderSystem
	${coreHeaders}
	${voxelHeaders}

	PARENT_SCOPE
)