add_subdirectory(Core)
# add_subdirectory(Voxels)

set(quartzSources
	${coreSources}
	${voxelSources}

	PARENT_SCOPE
)