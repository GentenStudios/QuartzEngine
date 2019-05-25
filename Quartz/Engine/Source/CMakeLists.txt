add_subdirectory(Core)
add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Graphics)
add_subdirectory(Utilities)

set(quartzSources
	${coreSources}
	${voxelSources}
	${mathSources}
	${graphicsSources}
	${utilitySources}

	PARENT_SCOPE
)
