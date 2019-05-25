add_subdirectory(Core)
add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Graphics)

set(quartzSources
	${coreSources}
	${voxelSources}
	${mathSources}
	${graphicsSources}

	PARENT_SCOPE
)
