add_subdirectory(Core)
add_subdirectory(Voxels)
add_subdirectory(Math)

set(quartzSources
	${coreSources}
	${voxelSources}
	${mathSources}

	PARENT_SCOPE
)
