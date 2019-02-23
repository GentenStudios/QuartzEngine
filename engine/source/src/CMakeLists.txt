add_subdirectory(core)
add_subdirectory(voxels)

set(quartzSources
	${coreSources}
	${voxelSources}

	PARENT_SCOPE
)